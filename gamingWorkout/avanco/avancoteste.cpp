#include <bits/stdc++.h>


//branco = 1
//preto = 2

int board[7][7];
int turn;
std::vector< std::pair<int, int> > blackpieces;
std::vector< std::pair<int, int> > whitepieces;
int nwhite;
int nblack;
std::vector< std::pair<int, int> > movesw;
std::vector< std::pair<int, int> > movesp;
std::vector< std::pair<int, int> > lastw;
std::vector< std::pair<int, int> > lastp;

void print();

void initGame () {
	for (int i=0;i<7;i++) {
		for (int j=0;j<7;j++) {
			if (i==0 || i==1) {
				blackpieces.push_back(std::make_pair(i,j));
				board[i][j] = 2;
			}
			else if (i==5 || i==6){
				whitepieces.push_back(std::make_pair(i,j));
				board[i][j] = 1;
			}
			else
				board[i][j] = 0;
		}
	}
}

bool validMove(int oldY, int oldX, int newY, int newX){
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

void possibleMoves() {
	movesw.clear();
	lastw.clear();
	movesp.clear();
	lastp.clear();
    for (int k=-1;k<2;k++) {
    	if (turn == 0){ //brancas primeiro a jogar, logo em numero par
    		for (int u=0; u<(int)whitepieces.size();u++) {
    			int i = whitepieces[u].first;
    			int j = whitepieces[u].second;
	    		if (j+k>=0 && j+k<7){
	    			if (k==0 && board[i-1][j]==0){
	    				lastw.push_back(std::make_pair(i,j));
	    				movesw.push_back(std::make_pair(i-1,j));
	    			}
	    			if (k!=0 && board[i-1][j+k]!=1){
	    				lastw.push_back(std::make_pair(i,j));
	    				movesw.push_back(std::make_pair(i-1,j+k));
	    			}
	    		}
	    	}
	    }
	    else {
	    	for (int u=0; u<(int)blackpieces.size();u++) {
	    		int i = blackpieces[u].first;
	    		int j = blackpieces[u].second;
	    		if (j+k>=0 && j+k<7){
	    			if (k==0 && board[i+1][j]==0){
	    				lastp.push_back(std::make_pair(i,j));
	    				movesp.push_back(std::make_pair(i+1,j));
	    			}
	    			if (k!=0 && board[i+1][j+k]!=2){
	    				lastp.push_back(std::make_pair(i,j));
	    				movesp.push_back(std::make_pair(i+1,j+k));
	    			}

		    	}
	   		}
		}

	}
}

void updateBoard (int Xnow, int Ynow,int moveX, int moveY) {
	printf("%d %d\n",Xnow,Ynow);
	//print();
	board[Xnow][Ynow] = 0;
	//printf("2\n");
	//print();
	//printf("\n");
    	if (turn == 0){
    		if (board[moveX][moveY] == 2) {    			
				for (int u=0; u<(int)blackpieces.size();u++) {
					int i = blackpieces[u].first;
					int j = blackpieces[u].second;

					if (i==moveX && j == moveY){
						blackpieces[u].first = -1;
						blackpieces[u].second = -1;
						nblack--;
					}
				}
    		}
    		board[moveX][moveY] = 1;
    		for (int u=0; u<(int)whitepieces.size();u++) {
    			int i = whitepieces[u].first;
    			int j = whitepieces[u].second;

    			if (i==Xnow && j == Ynow){
    				whitepieces[u].first=moveX;
    				whitepieces[u].second = moveY;
    			}
    		}
    	}
	    else{
    		if (board[moveX][moveY] == 1) {    			
				for (int u=0; u<(int)whitepieces.size();u++) {
					int i = whitepieces[u].first;
					int j = whitepieces[u].second;

					if (i==moveX && j == moveY){
						whitepieces[u].first = -1;
						whitepieces[u].second = -1;
						nwhite--;
					}
				}
    		}
			board[moveX][moveY] = 2;
			for (int u=0; u<(int)blackpieces.size();u++) {
				int i = blackpieces[u].first;
				int j = blackpieces[u].second;

				if (i==Xnow && j == Ynow){
					blackpieces[u].first=moveX;
					blackpieces[u].second = moveY;
				}
			}
		}


}
void playHuman(int Xnow, int Ynow,int moveY, int moveX) {
	if (validMove(Ynow,Xnow,moveY,moveX)){
    	updateBoard(Xnow,Ynow,moveY,moveX);
	}
    else {
    	while (!validMove(Ynow,Xnow,moveY,moveX)) {
    		printf ("Nao e possivel fazer a jogada\n");
    		scanf ("%d %d", moveX, moveY);
    	}
    }
}

void playBot() {
    srand(time(NULL));
    possibleMoves();
    std::pair<int,int> v;
    std::pair<int,int> a;
    if (turn==0) {
    	int t = rand()%(int)movesw.size();
	    v = movesw[t];
	    a = lastw[t];
	}
	else{
    	int t = rand()%(int)movesp.size();
	    v = movesp[t];
	    a = lastp[t];		
	}

   	int moveX = v.first;
   	int moveY = v.second;

   	int Xnow = a.first; //i anterior
   	int Ynow = a.second; //j anterior

   	updateBoard(Xnow,Ynow,moveX,moveY);
}

std::pair<int, int> chooseMove(){
	/*
    srand (time(NULL));
    std::vector<std::pair<int,int> > v = possibleMoves();
    int i = rand() % v.size();
    return v[i];
    */
}

int checkGameOver(){
	for (int i=0;i<7;i++) {
		if (board[0][i]==1)
			return 0;
		if (board[6][i]==2)
			return 1;
	}
	return -1;
}

void print() {
	for (int i=0;i<7;i++) {
		for (int j=0;j<7;j++) {
			if (board[i][j]==1)
				printf (" B");
			else if (board[i][j]==2)
				printf (" P");
			else
				printf(" -");
		}
		printf ("\n");
	}
		printf ("\n");
}

int main () {
	nwhite = 14;
	nblack = 14;
	initGame();
	printf ("inicial:\n");
	print();
	printf ("\n");
	turn =0;
	int x = 0;
	while (checkGameOver()==-1) {
		playBot();
		if (turn ==0)
			turn=1;
		else
			turn =0;
		print();
		x++;

		printf ("\n");
	}
	printf ("x = %d\n",x);
	print();
	return 0;
}
