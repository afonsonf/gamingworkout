#include "semaforo.h"
#include "ui_semaforo.h"

#include <iostream>
#include <vector>
#include <utility>
#include <time.h>

#include <QDebug>
#include <QMessageBox>


Semaforo::Semaforo(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::Semaforo)
{
    ui->setupUi(this);
    init_win();
    initGame();
    back = b;
}

Semaforo::~Semaforo()
{
    delete ui;
}

void Semaforo::init_win()
{
    ui->gridLayout->setSpacing(5);
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            m[i][j] = new QPushButton;
            m[i][j]->setFixedHeight(200);
            m[i][j]->setFixedWidth(200);
            connect(m[i][j],&QPushButton::clicked, [=]() {
                but_click(i,j);
            });
            m[i][j]->setStyleSheet("background-color: white");
            ui->gridLayout->addWidget(m[i][j],i,j);
        }
    }
    turn = 2;
    game_end=0;
    game_start = 1;
    first_player = 2;
}

void Semaforo::initGame() {
    for(int i=0; i<3; i++)
        for(int j=0; j<4; j++)
            this->board[i][j] = 'w';

    this->lastMoveX = -1;
    this->lastMoveY = -1;
}

void Semaforo::but_click(int i,int j)
{
    //qDebug() << turn << " " << i << " " << j << ;
    if(turn!=2 || game_end || (game_start && first_player == 1)) return;
    if(game_start)game_start =0;
    if(!validMove(i,j)){
        ui->mensagem->setText("Invalid move");
        return;
    }
    ui->mensagem->setText("");

    //play human
    playHuman(i,j);
    lastMoveX=j;
    lastMoveY=i;
    switch(board[lastMoveY][lastMoveX]){
        case 'g':{
            m[lastMoveY][lastMoveX]->setStyleSheet("background-color: green");
            break;
        }
        case 'y':{
            m[lastMoveY][lastMoveX]->setStyleSheet("background-color: yellow");
            break;
        }
        case 'r':{
            m[lastMoveY][lastMoveX]->setStyleSheet("background-color: red");
            break;
        }
    }

    if(end(board)){
        game_end = 1;
        QMessageBox::information(this,"Game ended","Ganhas-te!\n");
        return;
    }
    //play bot
    turn = 1;
    ui->mensagem->setText("thinking");
    QCoreApplication::processEvents();
    playBot();
    qDebug() << "butt " << board[lastMoveY][lastMoveX];
    ui->mensagem->setText("");
    switch(board[lastMoveY][lastMoveX]){
        case 'g':{
            m[lastMoveY][lastMoveX]->setStyleSheet("background-color: green");
            break;
        }
        case 'y':{
            m[lastMoveY][lastMoveX]->setStyleSheet("background-color: yellow");
            break;
        }
        case 'r':{
            m[lastMoveY][lastMoveX]->setStyleSheet("background-color: red");
            break;
        }
    }

    if(end(board)){
        game_end = 1;
        QMessageBox::information(this,"Game ended","Perdes-te!\n");
        return;
    }
    turn = 2;
}

std::array< std::array<char, 4>, 3> Semaforo::getBoard(){
    return this->board;
}

int Semaforo::getTurn(){
    return this->turn;
}

int Semaforo::getLastMoveX(){
    return this->lastMoveX;
}

int Semaforo::getLastMoveY(){
    return this->lastMoveY;
}

bool Semaforo::validMove(int moveY, int moveX){
    if(moveX > 3 || moveX < 0)
        return false;
    else if(moveY > 2 || moveY < 0)
        return false;
    else if(this->board[moveY][moveX] == 'r')
        return false;

    return true;
}

std::vector< std::pair<int, int> > Semaforo::possibleMoves(){
    std::vector< std::pair<int, int> > moves;

    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            std::cout << i << j << std::endl;
            if(validMove(i, j)){
                std::cout << i << j << std::endl;
                std::pair<int, int> arr = std::make_pair(i, j);
                moves.push_back(arr);
            }
        }
    }

    std::cout << "Possible moves:" << std::endl;
    for(unsigned int i=0; i<moves.size(); i++)
        std::cout << "y: " << moves[i].first << " x: " << moves[i].second << std::endl;

    qDebug()<<"ACABOU\n";

    return moves;
}

void Semaforo::playHuman(int moveY, int moveX){
    updateBoard(board,moveY, moveX);
}

std::pair<int, int> Semaforo::playBot(){
    std::pair<int, int> move = chooseMove();

    qDebug() << "PlayBot " << move.first << " " << move.second;

    updateBoard(board, move.first, move.second);
    lastMoveX = move.second;
    lastMoveY = move.first;
    return move;
}

void Semaforo::play(std::array< std::array<char,4>, 3> &b, std::pair<int,int> move){
    if(b[move.first][move.second] == 'w')
        b[move.first][move.second] = 'g';
    else if(b[move.first][move.second] == 'g')
        b[move.first][move.second] = 'y';
    else if(b[move.first][move.second] == 'y')
        b[move.first][move.second] = 'r';
}

int Semaforo::simul(std::array< std::array<char,4>, 3> b, int player)
{
  if(end(b))
    return (player+1)%2;

  std::vector<std::pair<int,int> > v;
  for(int i=0;i<3;i++)
    for(int j=0;j<4;j++)
      if(b[i][j]!='r')
      {
         v.push_back(std::make_pair(i,j));
      }
  std::pair<int,int> jog = v[rand()%v.size()];
/*
  //print
  for(int i=0;i<3;i++)
      for(int j=0;j<4;j++)
          printf("%c%c",b[i][j],(j==3)?'\n':' ');
  printf("\n");*/

  //printf("%d %d\n\n",jog.first,jog.second);
  play(b,jog);
/*
  //printf
  for(int i=0;i<3;i++)
      for(int j=0;j<4;j++)
          printf("%c%c",b[i][j],(j==3)?'\n':' ');
  printf("\n");*/

  return simul(b,(player%2)+1);
}

std::pair<int, int> Semaforo::chooseMove(){
    srand (time(NULL));
    std::vector<std::pair<int,int> > v = possibleMoves();
    //qDebug() << "AAAAAAAAA\n";

    int n = v.size();
    int score[n+10];
    for(int i=0;i<n;i++)
        score[i]=0;
    int NUM_JOGOS=10000;
    for(int g=0;g<NUM_JOGOS;g++)
      {
    for(int vi=0;vi<n;vi++)
      {
        std::array< std::array<char,4>, 3> b;
        for(int i=0;i<3;i++)
          for(int j=0;j<4;j++)
              b[i][j]=board[i][j];
        Semaforo::play(b,v[vi]);
        score[vi] += simul(b,2);/*
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<4;j++)
                qDebug() << b[i][j] << " ";
            qDebug() << "\n";
        }
        qDebug() << "\n";*/
      }
      }
    int max=0;
    for(int i=0;i<n;i++)
    {
        qDebug() << score[i];
      if(score[max]<score[i])
         max=i;
    }

    qDebug() << "CHOOSE " << v[max].first << " " << v[max].second;

    return v[max];
}

void Semaforo::updateBoard(std::array< std::array<char,4>, 3> &b, int moveY, int moveX){
    if(b[moveY][moveX] == 'w')
        b[moveY][moveX] = 'g';
    else if(b[moveY][moveX] == 'g')
        b[moveY][moveX] = 'y';
    else if(b[moveY][moveX] == 'y')
        b[moveY][moveX] = 'r';
}

bool Semaforo::end(std::array< std::array<char,4>, 3> b){
  //horizontal
  for(int i=0;i<3;i++)
    for(int j=0;j<2;j++)
      if(b[i][j]!='w' &&
     b[i][j+1]==b[i][j] &&
     b[i][j+2]==b[i][j])
    return true;

  //vertical
  for(int j=0;j<4;j++)
    if(b[0][j]!='w' &&
       b[1][j]==b[0][j] &&
       b[2][j]==b[0][j])
      return true;

  //up-right
  if(b[2][0]!='w' &&
     b[1][1]==b[2][0] &&
     b[0][2]==b[2][0])
    return true;
  if(b[2][1]!='w' &&
     b[1][2]==b[2][1] &&
     b[0][3]==b[2][1])
    return true;

  //down-right
  if(b[0][0]!='w' &&
     b[1][1]==b[0][0] &&
     b[2][2]==b[0][0])
    return true;
  if(b[0][1]!='w' &&
     b[1][2]==b[0][1] &&
     b[2][3]==b[0][1])
    return true;

  return false;
}

void Semaforo::on_pushButton_clicked()
{
    this->possibleMoves();
}

void Semaforo::on_sair_clicked()
{
    back->click();
}

void Semaforo::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(arg1=="human")first_player = 2;
    else first_player = 1;

    if(game_start && first_player==1){
        turn = 1;
        playBot();
        switch(board[lastMoveY][lastMoveX]){
            case 'g':{
                m[lastMoveY][lastMoveX]->setStyleSheet("background-color: green");
                break;
            }
            case 'y':{
                m[lastMoveY][lastMoveX]->setStyleSheet("background-color: yellow");
                break;
            }
            case 'r':{
                m[lastMoveY][lastMoveX]->setStyleSheet("background-color: red");
                break;
            }
        }
        if(end(board)){
            game_end = 1;
            QMessageBox::information(this,"Game ended","Perdes-te!\n");
            return;
        }
        turn = 2;
        game_start=0;
    }
}

void Semaforo::on_pushButton_2_clicked()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            m[i][j]->setStyleSheet("background-color: white");
        }
    }
    initGame();
    game_start = 1;
    game_end = 0;
    if(first_player == 1){
        turn = 1;
        playBot();
        switch(board[lastMoveY][lastMoveX]){
            case 'g':{
                m[lastMoveY][lastMoveX]->setStyleSheet("background-color: green");
                break;
            }
            case 'y':{
                m[lastMoveY][lastMoveX]->setStyleSheet("background-color: yellow");
                break;
            }
            case 'r':{
                m[lastMoveY][lastMoveX]->setStyleSheet("background-color: red");
                break;
            }
        }
        if(end(board)){
            game_end = 1;
            QMessageBox::information(this,"Game ended","Perdes-te!\n");
            return;
        }
        turn = 2;
        game_start=0;
    }
    else turn=2;
}
