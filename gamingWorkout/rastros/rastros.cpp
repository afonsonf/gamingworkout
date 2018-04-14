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

    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++) board[j][j]=0;

    turn = 0;
}

bool rastros::valid_move(int i, int j)
{
    return board[i][j] == 0;
}

std::vector<std::pair<int, int> > rastros::possible_moves(int xi,int xj)
{
    std::vector<std::pair<int,int> > v;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(xi+i>=0 && xi+i<7 && xj+j>=0 && xj+j<7){
                if(!(i==0 && j==0) && board[xi+i][xj+j]==0){
                    v.push_back(std::make_pair(xi+i,xj+j));
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
           (possible_moves(brancaI,brancaJ).size()==0);
}

bool rastros::playHuman(int i, int j)
{
    if(!valid_move(i,j)) return false;
    board[brancaI][brancaJ] = 1;
    brancaI = i;
    brancaJ = j;
    return true;
}

int rastros::heuristic(){
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

void rastros::playBot(){
    std::vector<std::pair<int,int> > v;
    v = possible_moves(brancaI,brancaJ);
    int i = rand() % v.size();
    board[brancaI][brancaJ] = 1;
    brancaI = v[i].first;
    brancaJ = v[i].second;
}

void rastros::on_sair_clicked()
{
    back->click();
}
