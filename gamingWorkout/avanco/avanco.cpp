#include "avanco.h"

#include <iostream>
#include <utility>
#include <time.h>
#include <vector>


//branco = 1
//preto = 2

avanco::avanco(){}

void avanco::initGame () {
	for (int i=0;i<7;i++) {
		for (int j=0;j<7;j++) {
			if (i==0 || i==1)
				board[i][j] = 2;
			else if (i==5 || i==6)
				board[i][j] = 1;
			else
				board[i][j] = 0;
		}
	}
}

bool avanco::validMove(int oldY, int oldX, int newY, int newX){
    if(newX > 6 || newX < 0)
        return false;
    else {
    	if (turn==0) {
    		if (newX-oldX!=-1 || -1>newY-oldY>1)
    			return false;
    		else{
    			if (board[newX][newY]==2 && newY-oldY==0)
    				return false;
    		}
    	}
    	else {    		
    		if (newX-oldX!=1 || -1>newY-oldY>1)
    			return false;
    		else{
    			if (board[newX][newY]==1 && newY-oldY==0)
    				return false;
    		}
    	}
    }

    return true;
}

std::vector< std::pair<int, int> > avanco::possibleMoves(int i, int j) {
    std::vector< std::pair<int, int> > moves;
    for (int k=-1;k<2;k++) {
    	if (this->turn == 0){ //brancas primeiro a jogar, logo em numero par
    		if (j+k>=0 && j+k<7){
    			if (k==0 && board[i--][j]==0)
    				moves.push_back(std::make_pair(i--,j));
    			if (k!=0 && board[i--][j+k]!=2)
    				moves.push_back(std::make_pair(i--,j+k));
    		}
    	}
    	else {
    		if (j+k>=0 && j+k<7){
    			if (k==0 && board[i++][j]==0)
    				moves.push_back(std::make_pair(i++,j));
    			if (k!=0 && board[i++][j+k]!=1)
    				moves.push_back(std::make_pair(i++,j+k));

	    	}
	    }

	}
	return moves;
}

void avanco::playHuman(int Xnow, int Ynow,int moveY, int moveX){
	if (validMove(Ynow,Xnow,moveY,moveX)){
    	board[Xnow][Ynow] = 0;
    	if (turn == 0)
    		board[moveX][moveY] = 1;
    	else
    		board[moveX][moveY] = 2;

	}
    else {
    	while (!validMove(Ynow,Xnow,moveY,moveX)) {
    		printf ("Nao e possivel fazer a jogada\n");
    		scanf ("%d %d", moveX, moveY);
    	}
    }
}

std::pair<int, int> avanco::playBot(){
	/*
    std::pair<int, int> move = chooseMove();

    updateBoard(move.first, move.second);
    lastMoveX = move.second;
    lastMoveY = move.first;
    return move;
    */
}

std::pair<int, int> avanco::chooseMove(){
	/*
    srand (time(NULL));
    std::vector<std::pair<int,int> > v = possibleMoves();
    int i = rand() % v.size();
    return v[i];
    */
}

int avanco::checkGameOver(){
	for (int i=0;i<7;i++) {
		if (board[0][i]==1)
			return 0;
		if (board[6][i]==2)
			return 1;
	}
	return -1;
}

int main () {

	return 0;
}
