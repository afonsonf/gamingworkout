#include "avanco.h"
#include "ui_avanco.h"

#include <iostream>
#include <vector>
#include <utility>
#include <time.h>

#include <QDebug>
#include <QMessageBox>


avanco::avanco(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::avanco)
{
    ui->setupUi(this);
}

avanco::~avanco()
{
    delete ui;
}

std::array< std::array<char, 7>, 7> avanco::getBoard(){
    return this->board;
}

int avanco::getTurn(){
    return this->turn;
}

int avanco::getLastMoveX(){
    return this->lastMoveX;
}

int avanco::getLastMoveY(){
    return this->lastMoveY;
}

bool avanco::validMove(int oldY, int oldX, int newY, int newX){
    if(newX > 6 || newX < 0)
        return false;
    else if(newY > 6 || newY < 0)
        return false;
    else if(std::abs(newX - oldX) > 1 || std::abs(newY - oldY) > 1)
        return false;
    else if(this->board[oldY][oldX] != turn)
        return false;
    else if(this->board[newY][newX] == turn)
        return false;
    else if((std::abs(newX - oldX) == 1 && std::abs(newY - oldY) == 0) && this->board[newY][newX] != 0)
        return false;
    else if(!(std::abs(newX - oldX) == 0 && std::abs(newY - oldY) == 1) && this->board[newY][newX] != 0)
        return false;

    return true;
}

std::vector< std::pair<int, int> > avanco::possibleMoves(){
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

void avanco::playHuman(int moveY, int moveX){
    updateBoard(moveY, moveX);
}

std::pair<int, int> avanco::playBot(){
    std::pair<int, int> move = chooseMove();

    updateBoard(move.first, move.second);
    lastMoveX = move.second;
    lastMoveY = move.first;
    return move;
}

std::pair<int, int> avanco::chooseMove(){
    srand (time(NULL));
    std::vector<std::pair<int,int> > v = possibleMoves();
    int i = rand() % v.size();
    return v[i];
}

void avanco::updateBoard(int moveY, int moveX){
    if(this->board[moveY][moveX] == 'w')
        this->board[moveY][moveX] = 'g';
    else if(this->board[moveY][moveX] == 'g')
        this->board[moveY][moveX] = 'y';
    else if(this->board[moveY][moveX] == 'y')
        this->board[moveY][moveX] = 'r';
}

bool avanco::checkGameOver(){
        //horizontal
        for(int i=0;i<3;i++)
          for(int j=0;j<2;j++)
        if(board[i][j]!='w' &&
           board[i][j+1]==board[i][j] &&
           board[i][j+2]==board[i][j])
          return true;

        //vertical
        for(int j=0;j<4;j++)
          if(board[0][j]!='w' &&
         board[1][j]==board[0][j] &&
         board[2][j]==board[0][j])
        return true;

        //up-right
        if(board[2][0]!='w' &&
           board[1][1]==board[2][0] &&
           board[0][2]==board[2][0])
          return true;
        if(board[2][1]!='w' &&
           board[1][2]==board[2][1] &&
           board[0][3]==board[2][1])
          return true;

        //down-right
        if(board[0][0]!='w' &&
           board[1][1]==board[0][0] &&
           board[2][2]==board[0][0])
          return true;
        if(board[0][1]!='w' &&
           board[1][2]==board[0][1] &&
           board[2][3]==board[0][1])
          return true;

        return false;
}

void avanco::on_pushButton_clicked()
{
    this->possibleMoves();
}

void avanco::on_sair_clicked()
{
    back->click();
}

void avanco::on_comboBox_2_currentIndexChanged(const QString &arg1)
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

void avanco::on_pushButton_2_clicked()
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
