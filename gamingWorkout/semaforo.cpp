#include "semaforo.h"
#include "ui_semaforo.h"

#include <iostream>
#include <array>
#include <vector>

class Node
{
private:
    std::array< std::array<char, 4>, 3> board;
    int turn; //1=human, 2=computer
    int lastMoveX;
    int lastMoveY;

public:
    Node() {
        for(int i=0; i<3; i++)
            for(int j=0; j<4; j++)
                this->board[i][j] = 'w';

        this->turn = 1;
        this->lastMoveX = -1;
        this->lastMoveY = -1;
    }

    Node(int turn) {
        for(int i=0; i<3; i++)
            for(int j=0; j<4; j++)
                this->board[i][j] = 'w';

        this->turn = turn;
        this->lastMoveX = -1;
        this->lastMoveY = -1;
    }

    Node(Node& parent, int moveX, int moveY) {
        std::array< std::array<char, 4>, 3> parentBoard = parent.getBoard();

        for(int i=0; i<3; i++)
            for(int j=0; j<4; j++)
                this->board[i][j] = parentBoard[i][j];

        if(this->board[moveY][moveX] == 'w')
            this->board[moveY][moveX] = 'g';
        else if(this->board[moveY][moveX] == 'g')
            this->board[moveY][moveX] = 'y';
        else
            this->board[moveY][moveX] = 'r';

        if(parent.getTurn() == 1)
            this->turn = 2;
        else
            this->turn = 1;

        this->lastMoveX = moveX;
        this->lastMoveY = moveY;
    }

    std::array< std::array<char, 4>, 3> getBoard(){
        return this->board;
    }

    int getTurn(){
        return this->turn;
    }

    int getLastMoveX(){
        return this->lastMoveX;
    }

    int getLastMoveY(){
        return this->lastMoveY;
    }



    bool validMove(int moveX, int moveY){
        if(moveX > 3 || moveX < 0)
            return false;
        else if(moveY > 2 || moveY < 0)
            return false;
        else if(this->board[moveY][moveX] == 'r')
            return false;

        return true;
    }

    std::vector< std::array<int, 2> > possibleMoves(){
        std::vector< std::array<int, 2> > moves;

        for(int i=0; i<3; i++)
            for(int j=0; j<4; j++)
                if(validMove(i, j)){
                    std::array<int, 2> arr = {i, j};
                    moves.push_back(arr);
                }

        std::cout << "moves std::array" << moves[0][0] << " " << moves[0][1] << std::endl;
        std::cout << "moves2 std::array" << moves[1][0] << " " << moves[1][1] << std::endl;

        return moves;
    }

};

Semaforo::Semaforo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Semaforo)
{
    ui->setupUi(this);

    Node node = Node();
    node.possibleMoves();
}

Semaforo::~Semaforo()
{
    delete ui;
}