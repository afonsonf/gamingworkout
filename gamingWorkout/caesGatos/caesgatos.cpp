#include "caesgatos.h"
#include "ui_caesgatos.h"

#include <QMessageBox>
#include <QDebug>

CaesGatos::CaesGatos(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::CaesGatos)
{
    ui->setupUi(this);
    back = b;
    init_win();
    initGame();
    depthmax = 3;
    dif = 0;
}


CaesGatos::~CaesGatos()
{
    delete ui;
}

void CaesGatos::init_win()
{
    ui->gridLayout->setSpacing(5);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            m[i][j] = new QPushButton;
            m[i][j]->setFixedHeight(70);
            m[i][j]->setFixedWidth(70);
            connect(m[i][j],&QPushButton::clicked, [=]() {
                but_click(i,j);
            });
            QPixmap pixmap(":/img/img/nada.png");
            QIcon ButtonIcon(pixmap);
            m[i][j]->setIcon(ButtonIcon);
            m[i][j]->setIconSize(pixmap.rect().size());
            ui->gridLayout->addWidget(m[i][j],i,j);
        }
    }
    turn = 0;
    game_end=0;
    game_start = 1;
    first_player = 0;
}

void CaesGatos::but_click(int i,int j)
{
    /*for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            qDebug() << i << " " << j << " " << board[(7-i)*10+j];
    */

    if(turn!=0 || game_end || (game_start && first_player == 1)) return;

    if(!validMove(2,(7-i)*10+j)){
        ui->mensagem->setText("invalid move");
        return;
    }
    nturn++;
    ui->mensagem->setText("");
    if(game_start)game_start =0;

    //play human
    qDebug() << (7-i)*10+j;
    playHuman((7-i)*10+j);
    if(first_player == 0){
        QPixmap pixmap1(":/img/img/gato.png");
        QIcon ButtonIcon1(pixmap1);
        m[i][j]->setIcon(ButtonIcon1);
        m[i][j]->setIconSize(m[i][j]->size());
    }
    else{
        QPixmap pixmap1(":/img/img/cao.png");
        QIcon ButtonIcon1(pixmap1);
        m[i][j]->setIcon(ButtonIcon1);
        m[i][j]->setIconSize(m[i][j]->size());
    }


    if(end()){
        game_end = 1;
        if(possMoves(1).size()==0) QMessageBox::information(this,"Game ended","You won!\n");
        else{
            QMessageBox::information(this,"Game ended","You lost!\n");
            ui->mensagem->setText(("Last Game win pos: row "+QString::number(7-possMoves(1)[0]/10)+", col "+QString::number(possMoves(1)[0]%10)));
        }
        return;
    }
/*
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++) qDebug() << (7-i) << " " << j << " " << board[(7-i)*10+j];
*/


    //play bot
    turn = 1;
    ui->mensagem->setText("thinking");
    QCoreApplication::processEvents();
    int move = playBot();
    ui->mensagem->setText("");
    std::vector<int> vv = possMoves(1);
    /*
    qDebug() << "A";
    for(int i=0;i<vv.size();i++)qDebug()<<vv[i];
    qDebug() << "B";
    qDebug() << "fin" << move;
    */
    if(first_player == 0){
        QPixmap pixmap1(":/img/img/cao.png");
        QIcon ButtonIcon1(pixmap1);
        m[7-move/10][move%10]->setIcon(ButtonIcon1);
        m[7-move/10][move%10]->setIconSize(m[7-move/10][move%10]->size());
    }
    else{
        QPixmap pixmap1(":/img/img/gato.png");
        QIcon ButtonIcon1(pixmap1);
        m[7-move/10][move%10]->setIcon(ButtonIcon1);
        m[7-move/10][move%10]->setIconSize(m[7-move/10][move%10]->size());
    }

    if(end()){
        game_end = 1;
        if(possMoves(1).size()==0) QMessageBox::information(this,"Game ended","You won!\n");
        else{
            ui->mensagem->setText(("Last Game win pos: row "+QString::number(7-move/10)+", col "+QString::number(move%10)));
            QMessageBox::information(this,"Game ended","You lost!\n");
        }
        return;
    }
    turn = 0;
}

void CaesGatos::on_sair_clicked()
{
    back->click();
}

int CaesGatos::alphabetaDecision(int maxDistanceDepth){
    if(nturn<2) depthmax = 2;
    else {
        switch(dif){
            case 0:
                depthmax = 1;
                break;
            case 1:
                depthmax = 2;
                break;
            case 2:
                depthmax = 4;
            break;
        }
    }
    int alpha = std::numeric_limits<int>::min(), beta = std::numeric_limits<int>::max();
    ABmaxValue(maxDistanceDepth,alpha,beta);

    return bestMove;
}

int CaesGatos::ABmaxValue(int maxDistanceDepth, int alpha, int beta){
    if(end())
        return -100;
    else if(maxDistanceDepth<=0)
        return possMoves(1).size() - possMoves(2).size();

    int v = std::numeric_limits<int>::min();
    int oldv = v;

    std::vector<int> moves = possMoves(1);
    int move;

    for(unsigned int i=0; i<moves.size(); i++){
        board[moves[i]] = 1;
        v = std::max(v, ABminValue(maxDistanceDepth-1, alpha, beta));
        board[moves[i]] = 0;
        if(oldv != v){
            oldv = v;
            move = moves[i];
        }

        if (v >= beta){
            bestMove = move;
            return v;
        }

        alpha = std::max(alpha, v);
    }

    bestMove = move;
    return v;
}

int CaesGatos::ABminValue(int maxDistanceDepth, int alpha, int beta){
    if(end())
        return 100;
    else if(maxDistanceDepth<=0)
        return possMoves(1).size() - possMoves(2).size();

    int v = std::numeric_limits<int>::max();

    std::vector<int> moves = possMoves(2);

    for(unsigned int i=0; i<moves.size(); i++){
        board[moves[i]] = 2;
        v = std::min(v, ABmaxValue(maxDistanceDepth-1, alpha, beta));
        board[moves[i]] = 0;

        if (v <= alpha)
            return v;

        beta = std::min(beta, v);
    }

    return v;
}

void CaesGatos::initGame()
{
  for(int i=0;i<100;i++)
      board[i] = 0;
  nturn = 0;
  game_start=1;
}

bool CaesGatos::validMove(int player,int move) //10*coluna + linha
{
  if(player==1)
    {
      /*qDebug() << "a" << move/10 << " " << move%10;
      if(move>=10)qDebug() << board[move-10];
      if(move%10>0)qDebug() << board[move-1];
      if(move<70)qDebug() << board[move+10];
      if(move%10<7)qDebug() << board[move+1];
      qDebug() << "b";*/

      if(board[move]==2 || board[move] == 1 ||
         (move>=10  && board[move-10]==2) ||
         (move%10>0 && board[move-1]==2) ||
         (move<70   && board[move+10]==2)  ||
         (move%10<7 && board[move+1]==2))
        return false;
    }
  else
    {/*
      qDebug() << "c" << move/10 << " " << move%10;
      if(move>=10)qDebug() << board[move-10];
      if(move%10>0)qDebug() << board[move-1];
      if(move<70)qDebug() << board[move+10];
      if(move%10<7)qDebug() << board[move+1];
      qDebug() << "d";
      */if(board[move]==2 || board[move] == 1 ||
           (move>=10 && board[move-10]==1) ||
         (move%10>0 && board[move-1]==1) ||
         (move<70 && board[move+10]==1)  ||
         (move%10<7 && board[move+1]==1))
        return false;
    }
  //qDebug() << "pp";
  if(game_start && move!=33 && move!=34 && move!=43 && move!=44)
    return false;


  return true;
}

int CaesGatos::playBot()
{
  int i = alphabetaDecision(depthmax);

  board[i] = 1;

  return i;
}

bool CaesGatos::playHuman(int move)
{
  if(!validMove(2,move))
    return false;

  board[move]=2;

  return true;
}

std::vector<int> CaesGatos::possMoves(int player)
{
  //qDebug() << "aa" << player;
  std::vector <int> v;
  if(game_start)
    {
      qDebug() << "pp";
      v.push_back(33);
      v.push_back(34);
      v.push_back(43);
      v.push_back(44);
      return v;
    }

  if(player==1)
    {
      for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      if(validMove(1,i*10+j))
        v.push_back(i*10+j);
    }
  else
    {
      for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      if(validMove(2,i*10+j))
        v.push_back(i*10+j);
    }
  return v;
}

bool CaesGatos::end()
{
  int np1 = possMoves(1).size();
  int np2 = possMoves(2).size();

  return (np1*np2)==0;
}

void CaesGatos::on_new_game_clicked()
{
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            QPixmap pixmap(":/img/img/nada.png");
            QIcon ButtonIcon(pixmap);
            m[i][j]->setIcon(ButtonIcon);
            m[i][j]->setIconSize(pixmap.rect().size());
        }
    }

    initGame();
    game_start = 1;
    game_end = 0;

    if(first_player == 1){
        qDebug() << "bot";
        turn = 1;

        turn = 1;
        int move = playBot();
        std::vector<int> vv = possMoves(1);

        if(first_player == 0){
            QPixmap pixmap1(":/img/img/cao.png");
            QIcon ButtonIcon1(pixmap1);
            m[7-move/10][move%10]->setIcon(ButtonIcon1);
            m[7-move/10][move%10]->setIconSize(m[7-move/10][move%10]->size());
        }
        else{
            QPixmap pixmap1(":/img/img/gato.png");
            QIcon ButtonIcon1(pixmap1);
            m[7-move/10][move%10]->setIcon(ButtonIcon1);
            m[7-move/10][move%10]->setIconSize(m[7-move/10][move%10]->size());
        }

        if(end()){
            game_end = 1;
            if(possMoves(1).size()==0) QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else QMessageBox::information(this,"Game ended","Perdes-te!\n");
            return;
        }
        turn = 0;

        turn = 0;
        game_start=0;
    }
    else turn=0;
}

void CaesGatos::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Human")first_player = 0;
    else first_player = 1;

    if(game_start && first_player==1){
        turn = 1;

        turn = 1;
        int move = playBot();
        std::vector<int> vv = possMoves(1);

        if(first_player == 0){
            QPixmap pixmap1(":/img/img/cao.png");
            QIcon ButtonIcon1(pixmap1);
            m[7-move/10][move%10]->setIcon(ButtonIcon1);
            m[7-move/10][move%10]->setIconSize(m[7-move/10][move%10]->size());
        }
        else{
            QPixmap pixmap1(":/img/img/gato.png");
            QIcon ButtonIcon1(pixmap1);
            m[7-move/10][move%10]->setIcon(ButtonIcon1);
            m[7-move/10][move%10]->setIconSize(m[7-move/10][move%10]->size());
        }

        if(end()){
            game_end = 1;
            if(possMoves(1).size()==0) QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else QMessageBox::information(this,"Game ended","Perdes-te!\n");
            return;
        }
        turn = 0;

        turn = 0;
        game_start=0;
    }
}

void CaesGatos::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "easy") dif = 0;
    else if (arg1 == "medium") dif = 1;
    else dif = 2;
}
