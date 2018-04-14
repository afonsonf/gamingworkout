#include <bits/stdc++.h>

int turn;
std::array< std::array<int, 9>, 9> board;
std::array< std::array<bool, 9>, 9> board2;
int nbrancas; //numero de brancas
int npretas; //numero de pretas
int prodb; //score total das pretas
int prodp; //score total das brancas
int grupop; //grupos de pretas
int grupob; //grupos de brancas
std::vector<int> gruposp;
std::vector<int> gruposb;
int first_player;
int max_depth;


void init();
int bfs (std::pair<int,int> r, int color);
std::vector<std::pair<int, int> > possibleMoves();
bool valid_move(int i, int j);
bool end();
int result();
bool playHuman(int i,int j, int color);
void playBot();
void print ();
void AlphaBeta ();
int min_value(int alpha, int beta, int depth);
int max_value(int alpha, int beta, int depth);

void init() 
{
	for (int i=0;i<9;i++) {
		for (int j=0;j<9;j++) {
			if (std::abs(i-j)>=5)
				board[i][j] = -1;
			else
				board[i][j] = 0;
		}
	}
	nbrancas = 0;
	npretas = 0;
}

std::vector<std::pair<int, int> > possibleMoves() 
{
	std::vector<std::pair<int,int> > p;
	for (int i=0;i<9;i++) {
		for (int j=0;j<9;j++) {
			if (board[i][j]==0)
				p.push_back(std::make_pair(i,j));
		}
	}
	return p;
}

bool valid_move(int i, int j)
{
	printf ("%d\n",board[i][j] );
    return board[i][j] == 0;
}

bool end() 
{
	if (nbrancas+npretas == 61)
		return true;
	else
		return false;
}

int result() {
	prodp = 1; 
	prodb = 1; 
	grupob = 0;
	grupop = 0;
	int val;
	for (int i =0 ;i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 1 && !(board2[i][j])){
				board2[i][j] = true;
				val= bfs (std::make_pair(i,j),board[i][j]);
				gruposp.push_back(-val);
				grupop++;
			}
			else if (board[i][j] == 2 && !(board2[i][j])){
				board2[i][j]= true;
				val = bfs (std::make_pair(i,j),board[i][j]);
				gruposb.push_back(-val);
				grupob++;
			}
		}
	}
	std::sort (gruposb.begin(),gruposb.end());
	std::sort (gruposp.begin(),gruposp.end());
	if (grupop>=2)
		prodp = gruposp[0]*gruposp[1];
	else
		prodp = 0;

	if (grupob>=2)
		prodb = gruposb[0]*gruposb[1];
	else
		prodb = 0;

	if (prodb > prodp)
		return 2; //ganharam as brancas
	else
		return 1; //ganharam as pretas

}

int bfs (std::pair<int,int> r, int color) {
	int afeta = 1;
	std::queue<std::pair<int,int> > q;
	q.push(r);
	while (!q.empty()) {
		int pi = q.front().first;
		int pj = q.front().second;
		q.pop();


		for (int i=-1;i<2;i++){
			for (int j=-1;j<2;j++) {
				if ((pi+i)>=0 && (pi+i)<9 && (pj+j)>=0 && (pj+j)<9 &&
					!(i==1 && j==-1) && !(i==-1 && j==1 )){
					if (board[pi+i][pj+j]==color && 
						!board2[pi+i][pj+j]){
						afeta++;
						q.push(std::make_pair(pi+i,pj+j));
						board2[pi+i][pj+j] = true;
					}
				}
			}
		}

	}

	return afeta;
}



bool playHuman(int i,int j, int color)
{
	if (!valid_move(i,j)) return false;
	board[i][j]=color; //1 preto, 2 branco
	if (color == 1)
		npretas++;
	else
		nbrancas++;
	return true;
}


void playBot()
{
    //AlphaBeta();
}


void print () {
	for (int i=0;i<9;i++) {
		for (int j=0; j<9;j++) {
			printf ("%d  ", board[i][j]);
		}
		printf ("\n");
	}
}

int main () {
	init();
	printf ("Quer ser o primeiro a jogar?\n(1)Sim\n(2)Nao\n");
	srand(time(NULL));
	bool correto =false;
	int li,co,color;
	scanf ("%d", &turn);
	print();
	if (turn == 1){
		first_player = 1;
		printf ("Escolha o lugar onde pretende jogar e a respetiva cor\nPreto:1 Branco:2\n");
		scanf ("%d %d %d", &li, &co, &color);
		correto =playHuman(li,co,color);
		while (!correto){
			printf ("Nao e possivel jogar nessa casa.. Tente outra vez\n\n");
			scanf ("%d %d %d", &li, &co, &color);
			correto =playHuman(li,co,color);
		}
		turn = 0;
		playBot();
		print();
	}
	else{
		first_player==2;
		playBot();
		turn = 1;
		print();
	}
	while (!end()) {
		if (turn==0){
			playBot();
			playBot();
			print();
			turn = 1;
		}
		else{
			printf ("Escolha os dois lugares onde pretende jogar e a respetiva cor\nPreto:1 Branco:2\n1º: ");
			scanf ("%d %d %d", &li, &co, &color);
			correto =playHuman(li,co,color);
			while (!correto){
				printf ("Nao e possivel jogar nessa casa.. Tente outra vez\n\n1º: ");
				scanf ("%d %d %d", &li, &co, &color);
				correto =playHuman(li,co,color);
			}
			printf ("2º:");
			scanf ("%d %d %d", &li, &co, &color);
			correto =playHuman(li,co,color);
			while (!correto){
				printf ("Nao e possivel jogar nessa casa.. Tente outra vez\n\n2º: ");
				scanf ("%d %d %d", &li, &co, &color);
				correto =playHuman(li,co,color);
			}
			playBot();
			playBot();
			print();
			turn = 0;
		}
	}

		int r =result();
		printf ("%d\n", r); 
		if ((r==1 && first_player==1) || (r==2 && first_player==2))
			printf ("Ganhou\n");
		else 
			printf ("Perderu\n");
}