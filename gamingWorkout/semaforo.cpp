#include "semaforo.h"
#include "ui_semaforo.h"

#include <iostream>
#include <vector>
#include <utility>



Semaforo::Semaforo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Semaforo)
{
    ui->setupUi(this);
}

Semaforo::~Semaforo()
{
    delete ui;
}

void Semaforo::initGame() {
    for(int i=0; i<3; i++)
        for(int j=0; j<4; j++)
            this->board[i][j] = 'w';

    this->turn = -1;
    this->lastMoveX = -1;
    this->lastMoveY = -1;
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

    return move;
}

std::pair<int, int> Semaforo::chooseMove(){
    return std::make_pair(0, 0);
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
    int n;
    //verify horizontal
    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            if(this->board[i][j] == 'r'){
                n=1;
                for(int k=1; k<3; k++)
                    if(this->board[i][j+k] == 'r')
                        n++;

                if(n == 3)
                    return true;
            }
        }
    }

    //verify vertical
    for(int i=0; i<4; i++){
        if(this->board[i][0] == 'r'){
            n=1;
            for(int k=1; k<3; k++)
                if(this->board[i][k] == 'r')
                    n++;

            if(n == 3)
                return true;
        }
    }

    //verify down/right
    for(int i=0; i<2; i++){
        if(this->board[0][i] == 'r'){
            n=1;
            for(int k=1; k<3; k++)
                if(this->board[k][i+k] == 'r')
                    n++;

            if(n == 3)
                return true;
        }
    }

    //verify down/left
    for(int i=3; i>1; i--){
        if(this->board[0][i] == 'r'){
            n=1;
            for(int k=1; k<3; k++)
                if(this->board[k][i-k] == 'r')
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
