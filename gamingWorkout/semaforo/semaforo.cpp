#include "semaforo.h"
#include "ui_semaforo.h"

#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <cmath>

#include <QDebug>
#include <QMessageBox>

using namespace std;

class Semaforo::node5{
public:
  std::array< std::array<char,4>, 3> tab;
  int player; //1pc , 2jog
  int win;
  int tot;
  node5 *parent;
  vector < node5* > child;
  node5(std::array< std::array<char,4>, 3> t, node5 *p, int pl)
  {
    tab=t;
    player=pl;
    win=0;
    tot=0;
    parent=p;
  }
};

void clean(Semaforo::node5* a,int b)
{
  if(a!=NULL)
    {
      for(int i=0;i<(int)a->child.size();i++)
	if(i!=b)
	  clean(a->child[i],-1);
      delete a;
    }
  return;
}





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
  if(!validMove(i,j)) return;
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

  return moves;
}

void Semaforo::playHuman(int moveY, int moveX){
  updateBoard(board,moveY, moveX);
}

std::pair<int, int> Semaforo::playBot(){
  std::pair<int, int> move = chooseMove();

  updateBoard(board,move.first, move.second);
  lastMoveX = move.second;
  lastMoveY = move.first;
  return move;
}

pair<int, int> Semaforo::chooseMove(){
  if(no5==NULL)
    no5 = new node5(board,NULL,1);
  int nos = 0;
  while(nos<1000)
    {
      MC(no5);
      nos++;
    }
  int jog = bestChoice(no5);
  node5 *t=no5;
  no5 = no5->child[jog];
  no5->parent=NULL; //no5 novo , t velho
  std::pair<int,int> papafonso;
  for(int i=0;i<3;i++)
      for(int j=0;j<4;j++)
          if(no5->tab[i][j] != t->tab[i][j])
          {
              papafonso = std::make_pair(i,j);
              i=5;j=10;
          }
  clean(t,jog);
  return papafonso;
}

void Semaforo::updateBoard(std::array< std::array<char,4>, 3> b, int moveY, int moveX){
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

double eval(Semaforo::node5 *t,int tot)
{
  if(t==NULL)
    return 0.5 + sqrt(2*log(tot+1));

  double wr = t->win/((double)t->tot+1);

  return wr + sqrt(2*log(tot+1)/((double)t->tot+1));
}

Semaforo::node5* select(Semaforo::node5 *t)
{
  if(end(t->tab))
    return t;
  vector <int> best;
  int score = 0;
  int tryi;
  for(int i=0;i<(int)t->child.size();i++)
    {
      tryi = (int)((eval(t->child[i],t->tot))*100000);
      if(tryi>score)
	{
	  best.clear();
	  best.push_back(i);
	  score = tryi;
	}
      else if(tryi==score)
	best.push_back(i);
    }
  int pick = best[rand()%(int)best.size()];
  if(score<(0.5 + sqrt(2*log(t->tot+1)))*100000 && (t->child.size())<(Semaforo::descend(t->tab).size()))
    {
      Semaforo::node5 *filho = new Semaforo::node5(Semaforo::play(t->tab,t,t->player%2+1);
      std::vector<std::array< std::array<char,4>, 3> > des = descend(t->tab);
      for(int p=0;p<(int)des.size();p++)
      {
          std::array< std::array<char,4>, 3> d = des[p];
          int c;
          for(c=0;i<(int)t->child.size();c++)
              if(d==t->child[i]->tab)
                  break;
          if(c==(int)t->child.size())
          {

          }
      }
      t->child.push_back(filho);
      return ;
    }
  return select(t->child[pick]);
}

std::vector <std::array< std::array<char,4>, 3> > descend(std::array< std::array<char,4>, 3> atu)
{
    std::vector <std::array< std::array<char,4>, 3> > v;
    for(int i=0;i<3;i++)
        for(int j=0;j<4;j++)
            if(atu[i][j]!='r')
                v.push_back(play(atu,std::make_pair(i,j)));
    return v;
}

std::array< std::array<char,4>, 3> play (std::array< std::array<char,4>, 3> t, pair<int,int> move)
{
  std::array< std::array<char,4>, 3> newBoard;
  for(int i=0;i<3;i++)
    for(int j=0;j<4;j++)
      newBoard[i][j] = t[i][j];
  Semaforo::updateBoard(newBoard, move.first, move.second);
  return newBoard;
}


int simul(std::array< std::array<char,4>, 3> tabi, int player)
{
  bool a = end(tabi);
  if(a)
    return a;
  
  vector <pair<int,int> > poss = possibleMoves();
  pair<int,int> pick = poss[rand()%(int)poss.size()];
  
  return simul(play(tabi,player,pick),(player%2)+1);
}

void update(Semaforo::node5 *t, int res)
{
  if(t==NULL)
    return;
  if(t->player==1)
    t->win+=res;
  else
    t->win+=(res+1)%2;
  (t->tot)++;
  return update(t->parent,res);
}

void MC(Semaforo::node5 *t)
{
  Semaforo::node5 *next = select(t);
  int res = simul(next->tab,next->player);
  update(next,res);
}

int bestChoice(Semaforo::node5 *t)
{
  int bMove;
  int score = -10000;
  int tryi;
  for(int i=0;i<(int)t->child.size();i++)
    {
      if(t->child[i]==NULL)
	continue;
      tryi = t->child[i]->tot;
      if(tryi > score)
	{
	  bMove=i;
	  score = tryi;
	}
    }
  return bMove;
}
