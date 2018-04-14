#include "semaforo.h"
#include "ui_semaforo.h"

#include <iostream>
#include <vector>
#include <utility>
#include <time.h>

#include <QDebug>
#include <QMessageBox>

typedef struct node<T>{
  T tab;
  int player; //1pc , 2jog
  int win;
  int tot;
  node<T> *parent;
  vector < node<T>* > child;
  node(T t, node<T> *p, int pl)
  {
    tab=t;
    player=pl;
    win=0;
    tot=0;
    parent=p;
  }
} node<T>;

void clean(node<T> *a,int b)
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

node < std::Array< std::Array<char,4>, 3> > T;

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
  if(checkGameOver()){
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
  if(checkGameOver()){
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

std::pair<int, int> Semaforo::chooseMove(){
  if(T==NULL)
    T = new node(board,NULL);
  int nos = 0;
  while(nos<1000)
    {
      MC(T);
      nos++;
    }
  pair<int,int> move = bestChoice(T);
  node *t=T;
  T = T->child[jog];
  T->parent=NULL;
  clean(t,jog);
  return move;
}

void Semaforo::updateBoard(std::Array< std::Array<char,4>, 3> > b, int moveY, int moveX){
  if(b[moveY][moveX] == 'w')
    b[moveY][moveX] = 'g';
  else if(b[moveY][moveX] == 'g')
    b[moveY][moveX] = 'y';
  else if(b[moveY][moveX] == 'y')
    b[moveY][moveX] = 'r';
}

bool Semaforo::end(std::Array< std::Array<char,4>, 3> b){
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
    if(checkGameOver()){
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
    if(checkGameOver()){
      game_end = 1;
      QMessageBox::information(this,"Game ended","Perdes-te!\n");
      return;
    }
    turn = 2;
    game_start=0;
  }
  else turn=2;
}

double eval(node *t,int tot)
{
  if(t==NULL)
    return 0.5 + EXPLOR_PARAM*sqrt(log(tot+1));

  double wr = t->win/((double)t->tot+1);
  if(!((t->tab)>>52))
    wr = 1.0 - wr;
  return wr + EXPLOR_PARAM*sqrt(log(tot+1)/((double)t->tot+1));
}

node* select(node *t)
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
  if(t->child[pick]==NULL)
    {
      t->child[pick] = new node(place(t->tab,pick),t);
      return t->child[pick];
    }
  return select(t->child[pick]);
}

std::Array< std::Array<char,4>, 3> > play (std::Array< std::Array<char,4>, 3> > t,int p, pair<int,int> move)
{
  std::Array< std::Array<char,4>, 3> > newBoard;
  for(int i=0;i<3;i++)
    for(int j=0;j<4;j++)
      newBoard[i][j] = t[i][j];
  updateBoard(newBoard,move.first, move.second);
  return newBoard;
}


int simul(T tabi, int player)
{
  bool a = end(tabi);
  if(a)
    return a;
  
  vector <pair<int,int> > poss = possibleMoves(player);
  pair<int,int> pick = poss[rand()%(int)poss.size()];
  
  return simul(play(tabi,player,pick),(player%2)+1);
}

void update(node *t, int res)
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

void MC(node<T> *t)
{
  node<T> *next = select(t);
  int res = simul(next->tab,next->player);
  update(next,res);
}

int bestChoice(node<T> *t)
{
  pair<int,int> bMove;
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
