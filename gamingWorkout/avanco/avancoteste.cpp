#include <bits/stdc++.h>


//branco = 1
//preto = 2

int board[7][7]; //tabuleiro atual
int turn; //turno atual, 0 para brancas, 1 para pretas
std::vector< std::pair<int, int> > blackpieces; //localizacao das pecas brancas
std::vector< std::pair<int, int> > whitepieces; //localizaco das pecas pretas
int nwhite; //numero de peca brancas
int nblack; //numero de pecas pretas
std::vector< std::pair<int, int> > movesw; //jogadas possiveis para as pecas brancas
std::vector< std::pair<int, int> > movesp; //jogadas possiveis para as pecas pretas
std::vector< std::pair<int, int> > lastw; //posicao anterior caso a jogada possivel seja efetuada (para brancas)
std::vector< std::pair<int, int> > lastp; //posicao anterior casa a jogada possivel seja efetuada (para pretas)
int player; //0 se for o primeiro a jogar, 1 caso contrario
int max_depth; //profundidade maxima
int best_play[2]; //i e j da melhor jogada
int ant_best_play[2]; //i e j anteriores a melhor jogada

void initGame ();
bool validMove(int oldY, int oldX, int newY, int newX);
void possibleMoves();
void updateBoard (int Xnow, int Ynow,int moveX, int moveY);
void playHuman(int Xnow, int Ynow,int moveX, int moveY);
void playBot();
int checkGameOver();
void print();
int heursistica ();
void AlphaBeta ();
int min_value(int alpha, int beta, int depth);
int max_value(int alpha, int beta, int depth);

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
void playHuman(int Xnow, int Ynow,int moveX, int moveY) {
	if (validMove(Ynow,Xnow,moveY,moveX)){
    	updateBoard(Xnow,Ynow,moveX,moveY);
	}
    else {
    	while (!validMove(Ynow,Xnow,moveY,moveX)) {
    		printf ("Nao e possivel fazer a jogada\n");
    		scanf ("%d %d", moveX, moveY);
    	}
    }
}

void playBot() {
	AlphaBeta();
	updateBoard(ant_best_play[0],ant_best_play[1],best_play[0],best_play[1]);
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

int heuristica () { //somatorio de quanto as pecas ja avancaram
	int f = checkGameOver();
	if (f!=-1) {
		if ((f==0 && player==0) || (f==1 && player==1))
			return -100;
		else
			return 100;
	}
	int vb=0; //heuristica para brancas
	int vp=0; //heuristica para pretas

	for (int i=0;i<(int)blackpieces.size();i++) {
		int fila = blackpieces[i].first;
		vp += std::abs(fila-0);
	}

	for (int i=0;i<(int)whitepieces.size();i++) {
		int fila = whitepieces[i].first;
		vb += std::abs(fila-6);
	}

	if (player==1)
		return vb-vp;
	
	return vp-vb;

}

void AlphaBeta () 
{
    int alpha = INT_MIN;
    int beta =INT_MAX;
    int depth = 0;
    if (turn == 0)
        min_value(alpha,beta,depth);
    else
        max_value(alpha,beta,depth);

}

int min_value(int alpha, int beta, int depth) 
{   
    if (checkGameOver() || depth>=max_depth) {
        return heuristica();
    }

    int val = INT_MAX, u;

    possibleMoves();
    int li; //i anteriror da peca branca
    int lj; //j anterior da peca branca
    int ni;
    int nj;
    int vlant; //valor anterior da peca onde vai ser joagado

    if (player==1) { //jogador um e as pretas
	    for (int i = 0; i < (int) movesp.size(); i++){
	        depth++;
	        ni = movesp[i].first;
	        nj = movesp[i].second;

	        li = lastp[i].first;
	        lj = lastp[i].second;

	        vlant = board [ni][nj];

	        board[ni][nj] = 2;

	        u = max_value(alpha,beta,depth);

	        if (val > u) {
	            if (depth==1){
	                best_play[0] = ni;
	                best_play[1] = nj;
	                ant_best_play[0] = li;
	                ant_best_play[1] = lj;
	            }
	            val = u;
	        }

	        if (val<=alpha)
	            return val;

	        beta = std::min (beta,val);
	        depth--;
	        board[li][lj] = 2;
	        board[ni][nj] = vlant;
	    }
	}
	else {
	    for (int i = 0; i < (int) movesw.size(); i++){
	        depth++;
	        ni = movesw[i].first;
	        nj = movesw[i].second;

	        li = lastw[i].first;
	        lj = lastw[i].second;

	        vlant = board [ni][nj];

	        board[ni][nj] = 1;

	        u = max_value(alpha,beta,depth);

	        if (val > u) {
	            if (depth==1){
	                best_play[0] = ni;
	                best_play[1] = nj;
	                ant_best_play[0] = li;
	                ant_best_play[1] = lj;
	            }
	            val = u;
	        }

	        if (val<=alpha)
	            return val;

	        beta = std::min (beta,val);
	        depth--;
	        board[li][lj] = 1;
	        board[ni][nj] = vlant;
	    }

	}
    return val;
}

int max_value(int alpha, int beta, int depth)
{  
    
    if (checkGameOver() || depth>=max_depth) {
        return heuristica();
    }

    int val = INT_MAX, u;

    possibleMoves();
    int li; //i anteriror da peca branca
    int lj; //j anterior da peca branca
    int vlant; //valor anterior da peca onde vai ser joagado
    int ni;
    int nj;

    if (player==0) { //jogador um e as brancas
	    for (int i = 0; i < (int) movesp.size(); i++){
	        depth++;
	        ni = movesp[i].first;
	        nj = movesp[i].second;

	        li = lastp[i].first;
	        lj = lastp[i].second;

	        vlant = board [ni][nj];

	        board[ni][nj] = 2;

	        u = min_value(alpha,beta,depth);

	        if (val < u) {
	            if (depth==1){
	                best_play[0] = ni;
	                best_play[1] = nj;
	                ant_best_play[0] = li;
	                ant_best_play[1] = lj;
	            }
	            val = u;
	        }

	        if (val>=beta)
	            return val;

	        alpha = std::min (alpha,val);
	        depth--;
	        board[li][lj] = 2;
	        board[ni][nj] = vlant;
	    }
	}
	else {
	    for (int i = 0; i < (int) movesw.size(); i++){
	        depth++;
	        ni = movesw[i].first;
	        nj = movesw[i].second;

	        li = lastw[i].first;
	        lj = lastw[i].second;

	        vlant = board [ni][nj];

	        board[ni][nj] = 1;

	        u = min_value(alpha,beta,depth);

	        if (val < u) {
	            if (depth==1){
	                best_play[0] = ni;
	                best_play[1] = nj;
	                ant_best_play[0] = li;
	                ant_best_play[1] = lj;
	            }
	            val = u;
	        }

	        if (val>=beta)
	            return val;

	        alpha = std::min (alpha,val);
	        depth--;
	        board[li][lj] = 1;
	        board[ni][nj] = vlant;
	    }
	}
    return val;

}



int main () {
	nwhite = 14;
	nblack = 14;
	initGame();
	printf ("inicial:\n");
	print();
	printf ("\n");
	printf ("Quer ser o primeiro a jogar?");
	scanf("%d", &player); //0 se for o primeiro, 1 caso contrario
	turn =0;
	int ia,ja,ie,je;
	while (checkGameOver()==-1) {
		if ((player==0 && turn==0) || (player == 1 && turn == 1)) {
			printf ("Indique a peca que quer mover e para onde: ");
			scanf ("%d %d %d %d", &ia, &ja, &ie, &je);
			playHuman(ia,ja,ie,je);
			
		}
		else 
			playBot();
		if (turn ==0)
			turn=1;
		else
			turn =0;
		print();
		printf ("\n");
	}
	print();
	return 0;
}
