#include <bits/stdc++.h>

using namespace std;

#define black 2
#define white 1

pair<int,int> branca = make_pair(4,4);
pair<int,int> casa1 = make_pair(0,0);
pair<int,int> casa2 = make_pair(6,6);
int turn; //1 turno do bot, 0 do jogador
int max_depth;
int li,co; //linha e coluna onde o jogador joga

class Node {
public:
	int config[7][7];
	int depth;
	pair<int,int> last_play;

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
	}

	int end() {
	vector < pair<int,int> > p = this->possible_moves(); 
	if (this->config[0][0] == white || (p.size()==0 && turn == 1))
		return 0;
	else if (this->config[6][6] == white || (p.size() == 0 
		&& turn == 0))
		return 1;

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
		int inb = x.first; //nova linha da branca
		int jnb = x.second; //nova coluna da branca
		this->config[inb][jnb] = white;
		branca = x;
	}

	int heuristic() {
		set<pair<int,int>,int> dist;
		queue<pair<int,int>> q;
		set<pair<int,int>,int>::iterator it;
		q.push(branca);
		dist.insert(branca,0);
		while (!q.empty()) {
			pair<int,int> x = q.pop();
			it = dist.find(x);

			if (x==)

		}

	}
};

bool playHuman(Node *x);
int playBot();
pair<int,int> minimax(Node *x);
int min_value (Node *x);
int max_value(Node *x);

pair<int,int> minimax(Node *x) {
	if (turn == 1)
		int heu = max_value (x);
	else
		int heu = min_value(x);
}

int min_value (Node *x) {
	int t = x->end();
	if (t > -1 || x->depth>=max_depth) { //valores de heurisitca extremos

	}
	int val = INT_MAX;
}

int max_value(Node *x) {
	if (x->end() > -1 || x->depth>=max_depth) { //valores de heuristica extremos
	
	}

	int val = INT_MIN;


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

int playBot () {

}

int main () {
	Node *x = new Node();
	printf ("Do you want to be the first to play?\n(1)Yes\n(2)No\nOption: ");
	scanf ("%d", &turn);
	if (turn == 2)
		turn = 1; //bot primeiro a jogar 
	else
		turn = 0;
	while (x->end()!=-1){
		if (turn == 0){
			bool jog =playHuman(x);
			while (!jog) {
				printf ("Jogada nao possivel. Tente outra vez\n");
				jog = playHuman(x);
			}
			pair<int,int> k = make_pair(li,co);
			x->play(k);
			turn = 1; 
		}
		else{ //turn=2 na primeira ronda caso seja o primeiro a jogar
			int x =playBot();
			turn = 0;
		}
	}
	
	return 0;
}