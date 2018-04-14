#include <bits/stdc++.h>

using namespace std;

#define black 2
#define white 1

pair<int,int> branca = make_pair(4,4);
pair<int,int> casa1 = make_pair(0,0); //casa do jogador 1
pair<int,int> casa2 = make_pair(6,6); //casa do jogador 2
int turn; //1 turno do bot, 0 do jogador
int first_player;
int max_depth;
int li,co; //linha e coluna onde o jogador joga

class Node {
public:
	int config[7][7];
	int depth;
	pair<int,int> last_play; //lugar para onde se moveu a branca na jogada anterior
	pair<int,int> last_branca; //lugar onde estava a branca na jogada anterior
	pair<int,int> best;

	Node () {
	for (int i=0;i<7;i++){
		for (int j=0; j<7;j++){
			if (i==4 && j==4)
				this->config[i][j] = white;
			else
				this->config[i][j]=0;
			}
		}
	this->depth=0;
	this->last_play = branca;
	this->last_branca = branca;
	this->best = make_pair(0,0);
	}

	int end() {
	vector < pair<int,int> > p = this->possible_moves();
	if (first_player==0) {
		if (this->config[0][0] == white || (p.size()==0 && turn == 1))
			return 0;
		else if (this->config[6][6] == white || (p.size() == 0 
			&& turn == 0))
			return 1;
	}
	else{ 
		if (this->config[6][6] == white || (p.size()==0 && turn == 1))
			return 0;
		else if (this->config[0][0] == white || (p.size() == 0 
			&& turn == 0))
			return 1;		
	}

	return -1;
	}

	vector < pair <int,int> > possible_moves(){
		int ib = branca.first;
		int jb = branca.second;
		vector < pair <int,int> >  p;
		for (int i=-1;i<2;i++) {
			for (int j=-1;j<2;j++) {
				if (ib+i>=0 && ib+i<=6 && jb+j>=0 && jb+j<=6){
					if (this->config[ib+i][jb+j]!=black 
						&& (i!=0 || j!=0))
						p.push_back(make_pair(ib+i,jb+j));
				}	
			}
		}
		return p;
	}

	void play (pair<int,int> x) {
		int ib = branca.first;
		int jb = branca.second;
		this->config[ib][jb] = black;
		this->last_branca = branca;
		int inb = x.first; //nova linha da branca
		int jnb = x.second; //nova coluna da branca
		this->config[inb][jnb] = white;
		branca = x;
		this->last_play = branca;
	}

	int heuristic_0() { //heuristica para o jogador
		pair<int,int> branca2=branca;
		vector<int> dist(56,0);
		vector<bool> visited(56,false);
		queue<pair<int,int>> q;
		q.push(branca);
		dist[branca.first + branca.second*7]=0;
		while (!q.empty()) {
			pair<int,int> x = q.front();
			q.pop();
			branca = x;
			int dist2 = dist[branca.first + branca.second*7];

			if (first_player==0) {
				if (x==casa1)
					return dist2;;
			}

			else{
				if (x==casa2)
					return dist2;
			}

			if (!visited[branca.first + branca.second*7]) {
				visited[branca.first + branca.second*7] = true;
				vector<pair<int,int> > p = this->possible_moves();
				for (int i=0; i< (int)p.size(); i++) {
					pair<int,int> g = p[i];
					if (!visited[g.first +g.second*7]){
						dist[g.first + g.second*7]=dist2+1;
						q.push(g);
					}
				}
			}

		}
		branca = branca2;
	}

	void removep (pair<int,int> lp,pair<int,int> lb) {
		branca = lb;
		int lia = lp.first;
		int lja = lp.second;
		int bia = lb.first;
		int bja = lb.second;
		this->config[lia][lja]=0;
		this->config[bia][bja]=white;
	}

	void print() {
		for (int i=0; i< 7;i++) {
			for (int j=0; j<7;j++) {
				if (this->config[i][j] == white)
					printf ("1");
				else if (this->config[i][j] == black)
					printf ("2");
				else
					printf("-");
			}
			printf ("\n");
		}
	}

};

bool playHuman(Node *x);
void playBot(Node *x);
pair<int,int> minimax(Node *x);
int min_value (Node *x);
int max_value(Node *x);

pair<int,int> minimax(Node *x) {
	if (turn == 1)
		int heu = max_value (x);
	else
		int heu = min_value(x);
	return x->best;
}

int min_value (Node *x) {
	int t = x->end();
	if (t > -1 || x->depth>=max_depth) { //valores de heurisitca extremos
		switch(t){
			case 1:
				return 100;
			case 0:
				return -100;
			default:
				return (-x->heuristic_0());
			}
	}
	int val = INT_MAX;
	int y;
	pair<int,int> lb = x->last_branca; 
	pair<int,int> lp = x->last_play;
	vector<pair<int,int>> p = x->possible_moves();
	for (int i=0; i<(int)p.size(); i++) {
		x->play(p[i]);
		y = max_value (x);

		if (val > y) {
			if (x->depth==1)
				x->best = x->last_play;
			val = y;
		}

		x->depth--;
		x->removep(lp,lb);
	}

	return val;
}

int max_value(Node *x) {
	int t = x->end();
	if (t > -1 || x->depth>=max_depth) { //valores de heurisitca extremos
		switch(t){
			case 1:
				return 100;
			case 0:
				return -100;
			default:
				return x->heuristic_0();
			}
	}
	int val = INT_MIN;
	int y;
	pair<int,int> lb = x->last_branca; 
	pair<int,int> lp = x->last_play;
	vector<pair<int,int>> p = x->possible_moves();
	for (int i=0; i<(int)p.size(); i++) {
		x->play(p[i]);
		y = min_value (x);

		if (val > y) {
			if (x->depth==1)
				x->best = x->last_play;
			val = y;
		}

		x->depth--;
		x->removep(lp,lb);
	}

	return val;
}

bool playHuman(Node *x) {	
	printf ("Linha e coluna onde pretende jogar: ");
	scanf ("%d %d", &li, &co);
	vector < pair <int,int> >  p = x->possible_moves();
	bool poss = false;
	for (int i=0; i<(int)p.size();i++) {
		if (p[i].first==li && p[i].second == co) {
			poss = true;
			break;
		}
	}
	return poss;
}

void playBot (Node *x) {
	pair<int,int> i = minimax(x);
	x->play(x->best);
}

int main () {
	Node *x = new Node();
	printf ("Do you want to be the first to play?\n(1)Yes\n(2)No\nOption: ");
	scanf ("%d", &turn);
	if (turn == 2){
		turn = 1; //bot primeiro a jogar
		first_player = 1; 
	}
	else{
		turn = 0;
		first_player = 0;
	}
	x->print();
	//printf ("k = %d", x->end());
	while (x->end()!=0 || x->end()!=1){
		if (turn == 0){
			bool jog =playHuman(x);
			while (!jog) {
				printf ("Jogada nao possivel. Tente outra vez\n");
				jog = playHuman(x);
			}
			pair<int,int> k = make_pair(li,co);
			x->play(k);
			turn = 1; 
			x->print();
		}
		else{ //turn=2 na primeira ronda caso seja o primeiro a jogar
			playBot(x);
			turn = 0;
			x->print();
		}
	}
	
	return 0;
}