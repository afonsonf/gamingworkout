#include <bits/stdc++.h>

using namespace std;

int board[100]; // 10*coluna + linha
int bestMove;
int start_game;

void initGame();
bool validMove(int player,int move);
int playBot();
bool playHuman(int move);
void undoPlay(int move);
vector<int> possMoves(int player);
bool end();

int alphabetaDecision(int maxDistanceDepth);
int ABmaxValue(int maxDistanceDepth, int alpha, int beta);
int ABminValue(int maxDistanceDepth, int alpha, int beta);

int alphabetaDecision(int maxDistanceDepth){
    int alpha = numeric_limits<int>::min(), beta = numeric_limits<int>::max();
    int v = ABmaxValue(maxDistanceDepth);

    return bestMove;
}

int ABmaxValue(int maxDistanceDepth, int alpha, int beta){
    if(end())
        return -100;
    else if(maxDistanceDepth<=0)
        return possMoves(1).size() - possMoves(2).size();

    int v = numeric_limits<int>::min();
    int oldv = v;

    vector<int> moves = possMoves(1);
    int move;

    for(unsigned int i=0; i<moves.size(); i++){
        board[moves[i]] = 1;
        v = max(v, ABminValue(maxDistanceDepth-1, alpha, beta));
        board[moves[i]] = 0;
        if(oldv != v){
            oldv = v;
            move = moves[i];
        }

        if (v >= beta){
            bestMove = move;
            return v;
        }

        alpha = max(alpha, v);
    }

    bestMove = move;
    return v;
}

int ABminValue(int maxDistanceDepth, int alpha, int beta){
    if(end())
        return 100;
    else if(maxDistanceDepth<=0)
        return possMoves(1).size() - possMoves(2).size();

    int v = numeric_limits<int>::max();

    vector<int> moves = possMoves(2);

    for(unsigned int i=0; i<moves.size(); i++){
        board[moves[i]] = 2;
        v = min(v, ABmaxValue(maxDistanceDepth-1, alpha, beta));
        board[moves[i]] = 0;

        if (v <= alpha)
            return v;

        beta = min(beta, v);
    }

    return v;
}

void initGame()
{
  for(int i=0;i<100;i++)
      board[i] = 0;

  start_game=0;
}

bool validMove(int player,int move) //10*coluna + linha
{
  if(player==1)
    {
      if((move>=10 && board[move-10]==2) ||
	 (move%10>0 && board[move-1]==2) ||
	 (move<70 && board[move+10]==2)  ||
	 (move%10<7 && board[move+1]==2))
	return false;
    }
  else
    {
      if((move>=10 && board[move-10]==1) ||
	 (move%10>0 && board[move-1]==1) ||
	 (move<70 && board[move+10]==1)  ||
	 (move%10<7 && board[move+1]==1))
	return false;
    }

  if(!start_game && move!=33 && move!=34 && move!=43 && move!=44)
    return false;

  
  return true;
}

int playBot()
{
  int i = alphabetaDecision(5);

  board[p[i]] = 1;

  return p[i];
}

bool playHuman(int move)
{
  if(!validMove(2,move))
    return false;

  board[move]=2;
  
  return true;
}

vector<int> possMoves(int player)
{
  vector <int> v;
  if(!start_game)
    {
      v.push_back(33);
      v.push_back(34);
      v.push_back(43);
      v.push_back(44);
      return v;
    }
  
  if(player==1)
    {
      for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	  if(validMove(1,i*10+j))
	    v.push_back(i*10+j);
    }
  else
    {
      for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	  if(validMove(2,i*10+j))
	    v.push_back(i*10+j);
    }
  return v;
}

bool end()
{
  int np1 = possMoves(1).size();
  int np2 = possMoves(2).size();
  
  return (np1*np2)==0;
}

int main()
{
  int turn;
  printf("wanna be first? 1no 2yes\n");
  scanf("%d",&turn);

  initGame();
  
  while(!end())
    {
      if(turn==1)
	{
	  int a = playBot();
	  turn=2;
	}
      else
	{
	  for(int j=7;j>=0;j--)
	    for(int i=0;i<8;i++)
	      {
		printf("%d",board[i*10+j]);
		if(i==7)
		  printf("\n");
	      }
	  int move;
	  scanf("%d",&move);
	  while(!playHuman(move))
	    {
	      printf("besta\n");
	      scanf("%d",&move);
	    }
	  turn=1;
	}
    }

  return 0;
}
