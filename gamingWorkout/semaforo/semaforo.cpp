#include "semaforo/semaforo.h"
#include "ui_semaforo.h"

#include <iostream>
#include <vector>
#include <utility>
#include <time.h>

#include <QDebug>
#include <QMessageBox>

QPushButton *back;

QPushButton *m[3][4];
int game_end;
int game_start;
int first_player;

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
    if(turn!=2 || game_end || (game_start && first_player == 1)) return;
    if(game_start)game_start =0;
    if(!validMove(i,j)) return;
    //play human
    playHuman(i,j);
    lastMoveX=j;
    lastMoveY=i;
    qDebug() << turn << " " << i << " " << j << " " << board[lastMoveY][lastMoveX] << "0";
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
    updateBoard(moveY, moveX);
}

std::pair<int, int> Semaforo::playBot(){
    std::pair<int, int> move = chooseMove();

    updateBoard(move.first, move.second);
    lastMoveX = move.second;
    lastMoveY = move.first;
    return move;
}

std::pair<int, int> Semaforo::chooseMove(){
    srand (time(NULL));
    std::vector<std::pair<int,int> > v = possibleMoves();
    int i = rand() % v.size();
    return v[i];
}

void Semaforo::updateBoard(int moveY, int moveX){
    if(this->board[moveY][moveX] == 'w')
        this->board[moveY][moveX] = 'g';
    else if(this->board[moveY][moveX] == 'g')
        this->board[moveY][moveX] = 'y';
    else if(this->board[moveY][moveX] == 'y')
        this->board[moveY][moveX] = 'r';
}

bool Semaforo::checkGameOver(){
   // return false;
    int n;
    //verify horizontal
    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            if(this->board[i][j] != 'w'){
                n=1;
                for(int k=1; k<3; k++)
                    if(this->board[i][j+k] == this->board[i][j])
                        n++;

                if(n == 3)
                    return true;
            }
        }
    }

    //verify vertical
    for(int i=0; i<4; i++){
        if(this->board[0][i] != 'w'){
            n=1;
            for(int k=1; k<3; k++)
                if(this->board[k][i] == this->board[0][i])
                    n++;

            if(n == 3)
                return true;
        }
    }

    //verify down/right
    for(int i=0; i<2; i++){
        if(this->board[0][i] != 'w'){
            n=1;
            for(int k=1; k<3; k++)
                if(this->board[k][i+k] == this->board[0][i])
                    n++;

            if(n == 3)
                return true;
        }
    }

    //verify down/left
    for(int i=3; i>1; i--){
        if(this->board[0][i] != 'w'){
            n=1;
            for(int k=1; k<3; k++)
                if(this->board[k][i-k] == this->board[0][i])
                    n++;

            if(n == 3)
                return true;
        }
    }

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
