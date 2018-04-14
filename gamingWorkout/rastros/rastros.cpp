#include "rastros.h"
#include "ui_rastros.h"

#include <queue>

rastros::rastros(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::rastros)
{
    ui->setupUi(this);
    back = b;
}

rastros::~rastros()
{
    delete ui;
}

void rastros::init()
{
    brancaI = 4;
    brancaJ = 4;
    pfinal[0][0] = 0;
    pfinal[0][1] = 0;

    pfinal[1][0] = 6;
    pfinal[1][1] = 6;

    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++) board[j][j]=0;

    turn = 1;
}

bool rastros::valid_move(int i, int j)
{
    return board[i][j] == 0;
}

std::vector<std::pair<int, int> > rastros::possible_moves()
{
    std::vector<std::pair<int,int> > v;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(brancaI+i>=0 && brancaI+i<6 && brancaJ+j>=0 && brancaJ+j<6){
                if(!(i==0 && j==0) && board[brancaI+i][brancaJ+j]==0){
                    v.push_back(std::make_pair(brancaI+i,brancaJ+j));
                }
            }
        }
    }
    return v;
}

bool rastros::end()
{
    return (brancaI == pfinal[0][0] && brancaJ == pfinal[0][1]) ||
           (brancaI == pfinal[1][0] && brancaJ == pfinal[1][1]) ||
           (possible_moves().size()==0);
}

bool rastros::playHuman(int i, int j)
{
    if(!valid_move(i,j)) return false;
    board[brancaI][brancaJ] = 1;
    brancaI = i;
    brancaJ = j;
    return true;
}

int rastros::heuristic()
{
    if(end()){
        if(brancaI == pfinal[0][0]) return -100;
        if(brancaJ == pfinal[1][0]) return  100;
        if(turn == 0) return 100;
        else return -100;
    }
    std::queue<std::pair<std::pair<int,int>,int > > q;
    std::vector<std::pair<int,int> > v;
    int vis[7][7];
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            vis[i][j] = board[i][j];
        }
    }
    q.push(std::make_pair(std::make_pair(brancaI,brancaJ),0));
    vis[brancaI][brancaJ]=1;
    int p0 = -1,p1=-1,ix,jx,t;
    while(q.size()>0){
        ix = q.front().first.first;
        jx = q.front().first.second;
        t = q.front().second;
        q.pop();
        if(brancaI == pfinal[0][0] && brancaJ == pfinal[0][1]){
            p0 = t;
        }
        if(brancaI == pfinal[1][0] && brancaJ == pfinal[1][1]){
            p1 = t;
        }
        v = possible_moves(ix,jx);
        for(int i=0;i<(int)v.size();i++){
            if(vis[v[i].first][v[i].second]){
                q.push(std::make_pair(std::make_pair(v[i].first,v[i].second),t+1));
                vis[v[i].first][v[i].second] = 1;
            }

        }
    }
    if(p0==-1)p0=0;
    if(p1==-1)p1=0;
    return p1-p0;

}

void rastros::playBot()
{
    AlphaBeta();
    board[brancaI][brancaJ] = 1;
    brancaI = best_play[0];
    brancaJ = best_play[1];
}

void rastros::AlphaBeta () 
{
    int alpha = INT_MIN;
    int beta =INT_MAX;
    int depth = 0;
    if (turn == 0)
        min_value(alpha,beta,depth);
    else
        max_value(alpha,beta,depth);

}

int rastros::min_value(int alpha, int beta, int depth) 
{   
    if (end() || depth>=max_depth) {
        return heuristic();
    }

    int val = INT_MAX, u;

    std::vector<std::pair<int,int> > p;
    p = possible_moves();
    int lpi = brancaI;
    int lpj = brancaJ;
    int nbi; //novo i da peca branca
    int nbj; //novo j da peca branca
    for (int i = 0; i < (int) p.size(); i++){
        depth++;
        nbi = p[i].first;
        nbj = p[i].second;

        brancaI = nbi;
        brancaJ = nbj;

        board[lpi][lpj] = 1;

        u = max_value(alpha,beta,depth);

        if (val > u) {
            if (depth==1){
                best_play[0] = nbi;
                best_play[1] = nbj;
            }
            val = u;
        }

        if (val<=alfa)
            return val;

        beta = std::min (beta,val);
        depth--;
        board[nbi][nbp] = 0;
        board[lpi][lpj] = 0;
        brancaI = lpi;
        brancaJ = lpj;

    }

    return val;
}

int rastros::max_value(int alpha, int beta, int depth)
{  
    if (end() || depth>=max_depth) {
        return heuristic();
    }

    int val = INT_MIN, u;

    std::vector<std::pair<int,int> > p;
    p = possible_moves();
    int lpi = brancaI;
    int lpj = brancaJ;
    int nbi; //novo i da peca branca
    int nbj; //novo j da peca branca
    for (int i = 0; i < (int) p.size(); i++){
        depth++;
        nbi = p[i].first;
        nbj = p[i].second;

        brancaI = nbi;
        brancaJ = nbj;

        board[lpi][lpj] = 1;

        u = min_value(alpha,beta,depth);

        if (val < u) {
            if (depth==1){
                best_play[0] = nbi;
                best_play[1] = nbj;
            }
            val = u;
        }

        if (val>=beta)
            return val;

        alpha = std::min (alpha,val);
        depth--;
        board[nbi][nbp] = 0;
        board[lpi][lpj] = 0;
        brancaI = lpi;
        brancaJ = lpj;

    }

    return val;

}

void rastros:print (){
        for (int i=0; i< 7;i++) {
            printf ("%d ",i);
            for (int j=0; j<7;j++) {
                if (board[i][j] == 1)
                    printf (" B");
                else if (board[i][j] == 0 && (i==brancaI && j == brancaJ))
                    printf (" W");
                else
                    printf(" -");
            }
            printf ("\n");
        }
        printf ("  ");
        for (int i=0;i<7;i++)
            printf (" %d",i);
        printf ("\n");


}

