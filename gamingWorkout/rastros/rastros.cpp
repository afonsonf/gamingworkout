#include "rastros.h"
#include "ui_rastros.h"

#include <queue>
#include <iostream>
#include <QMessageBox>
#include <QDebug>

rastros::rastros(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::rastros)
{
    ui->setupUi(this);
    back = b;
    max_depth =10;
    init_win();
    init();
}

void rastros::init_win()
{
    ui->gridLayout->setSpacing(5);
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            m[i][j] = new QPushButton;
            m[i][j]->setFixedHeight(75);
            m[i][j]->setFixedWidth(75);
            connect(m[i][j],&QPushButton::clicked, [=]() {
                but_click(i,j);
            });
            QPixmap pixmap(":/img/img/nada.png");
            QIcon ButtonIcon(pixmap);
            m[i][j]->setIcon(ButtonIcon);
            m[i][j]->setIconSize(pixmap.rect().size());
            ui->gridLayout->addWidget(m[i][j],i,j);
        }
    }
    QPixmap pixmap1(":/img/img/1.png");
    QIcon ButtonIcon1(pixmap1);
    m[6][0]->setIcon(ButtonIcon1);
    m[6][0]->setIconSize(m[6][0]->size());
    QPixmap pixmap2(":/img/img/2.png");
    QIcon ButtonIcon2(pixmap2);
    m[0][6]->setIcon(ButtonIcon2);
    m[0][6]->setIconSize(m[0][6]->size());
    QPixmap pixmap3(":/img/img/branca.png");
    QIcon ButtonIcon3(pixmap3);
    m[2][4]->setIcon(ButtonIcon3);
    m[2][4]->setIconSize(m[2][4]->size());
    turn = 0;
    game_end=0;
    game_start = 1;
    first_player = 0;
}

void rastros::but_click(int i,int j)
{
    qDebug()<<0;
    if(turn!=0 || game_end || (game_start && first_player == 1)) return;
    if(game_start)game_start =0;
    qDebug()<<1;
    if(!valid_move(6-i,j)) return;
    qDebug()<<2;
    //play human
    QPixmap pixmap1(":/img/img/preta.png");
    QIcon ButtonIcon1(pixmap1);
    m[6-brancaI][brancaJ]->setIcon(ButtonIcon1);
    m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
    playHuman(6-i,j);
    QPixmap pixmap2(":/img/img/branca.png");
    QIcon ButtonIcon2(pixmap2);
    m[6-brancaI][brancaJ]->setIcon(ButtonIcon2);
    m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());

    if(end()){
        game_end = 1;
        if(first_player==0){
            if(brancaI==pfinal[0][0] && brancaJ==pfinal[0][1])
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else if(brancaI==pfinal[1][0] && brancaJ==pfinal[1][1])
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            else
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            return;
        }
        else{
            if(brancaI==pfinal[1][0] && brancaJ==pfinal[1][1])
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else if(brancaI==pfinal[0][0] && brancaJ==pfinal[0][1])
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            else
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            return;
        }
    }
    //play bot
    turn = 1;
    m[6-brancaI][brancaJ]->setIcon(ButtonIcon1);
    m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
    playBot();
    m[6-brancaI][brancaJ]->setIcon(ButtonIcon2);
    m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
    if(end()){
        game_end = 1;
        if(first_player==0){
            if(brancaI==pfinal[0][0] && brancaJ==pfinal[0][1])
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else if(brancaI==pfinal[1][0] && brancaJ==pfinal[1][1])
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            else
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            return;
        }
        else{
            if(brancaI==pfinal[1][0] && brancaJ==pfinal[1][1])
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else if(brancaI==pfinal[0][0] && brancaJ==pfinal[0][1])
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            else
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            return;
        }
    }
    turn = 0;
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
        for(int j=0;j<7;j++) board[i][j]=0;
/*
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++) std::cout << board[i][j] + " ";
        std::cout << "\n";
    }*/
}

bool rastros::valid_move(int i, int j)
{
    int ki,kj;
    ki = abs(i-brancaI);
    kj = abs(j-brancaJ);
    /*qDebug() <<i<<" "<<j<< " a " << board[i][j] <<" "<<ki<< " " << kj;
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++) std::cout << board[i][j] + " ";
        std::cout << "\n";
    }*/

    return board[i][j] == 0 && ki<=1 && kj<=1;
}

std::vector<std::pair<int, int> > rastros::possible_moves(int ix,int jx)
{
    std::vector<std::pair<int,int> > v;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(ix+i>=0 && ix+i<7 && jx+j>=0 && jx+j<7){
                if(!(i==0 && j==0) && board[ix+i][jx+j]==0){
                    v.push_back(std::make_pair(ix+i,jx+j));
                }
            }
        }
    }
    return v;
}

bool rastros::end()
{
    //qDebug() << brancaI << " " << brancaJ << " " <<possible_moves(brancaI,brancaJ).size();
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
    if (first_player == 1)
        min_value(alpha,beta,depth);
    else{
        max_value(alpha,beta,depth);
        qDebug()<<"max!!\n";
    }

}

int rastros::min_value(int alpha, int beta, int depth)
{
    if (end() || depth>=max_depth) {
        return heuristic();
    }

    int val = INT_MAX, u;

    std::vector<std::pair<int,int> > p;
    p = possible_moves(brancaI,brancaJ);
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

        if (val<=alpha){
            board[nbi][nbj] = 0;
            board[lpi][lpj] = 0;
            brancaI = lpi;
            brancaJ = lpj;
            return val;
        }
        beta = std::min (beta,val);
        depth--;
        board[nbi][nbj] = 0;
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
    p = possible_moves(brancaI,brancaJ);
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

        if (val>=beta){
            board[nbi][nbj] = 0;
            board[lpi][lpj] = 0;
            brancaI = lpi;
            brancaJ = lpj;
            return val;
        }
        alpha = std::min (alpha,val);
        depth--;
        board[nbi][nbj] = 0;
        board[lpi][lpj] = 0;
        brancaI = lpi;
        brancaJ = lpj;

    }

    return val;
}

void rastros::on_sair_clicked()
{
    back->click();
}

void rastros::on_new_game_clicked()
{
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            QPixmap pixmap(":/img/img/nada.png");
            QIcon ButtonIcon(pixmap);
            m[i][j]->setIcon(ButtonIcon);
            m[i][j]->setIconSize(pixmap.rect().size());
        }
    }
    qDebug()<<"new game";
    QPixmap pixmap1(":/img/img/1.png");
    QIcon ButtonIcon1(pixmap1);
    m[6][0]->setIcon(ButtonIcon1);
    m[6][0]->setIconSize(m[6][0]->size());
    QPixmap pixmap2(":/img/img/2.png");
    QIcon ButtonIcon2(pixmap2);
    m[0][6]->setIcon(ButtonIcon2);
    m[0][6]->setIconSize(m[0][6]->size());
    QPixmap pixmap3(":/img/img/branca.png");
    QIcon ButtonIcon3(pixmap3);
    m[2][4]->setIcon(ButtonIcon3);
    m[2][4]->setIconSize(m[2][4]->size());

    QPixmap pixmapx0(":/img/img/preta.png");
    QIcon ButtonIconpreto(pixmapx0);
    QPixmap pixmapx1(":/img/img/branca.png");
    QIcon ButtonIconbranco(pixmapx1);

    init();
    game_start = 1;
    game_end = 0;

    if(first_player == 1){
        qDebug() << "bot";
        turn = 1;
        m[6-brancaI][brancaJ]->setIcon(ButtonIconpreto);
        m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
        playBot();
        m[6-brancaI][brancaJ]->setIcon(ButtonIconbranco);
        m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
        if(end()){
            game_end = 1;
            if(brancaI==pfinal[0][0] && brancaJ==pfinal[0][1])
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else if(brancaI==pfinal[1][0] && brancaJ==pfinal[1][1])
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            else
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            return;
        }
        turn = 0;
        game_start=0;
    }
    else turn=0;
}

void rastros::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1=="Human")first_player = 0;
    else first_player = 1;

    QPixmap pixmap1(":/img/img/preta.png");
    QIcon ButtonIcon1(pixmap1);
    QPixmap pixmap2(":/img/img/branca.png");
    QIcon ButtonIcon2(pixmap2);

    if(game_start && first_player==1){
        turn = 1;
        m[6-brancaI][brancaJ]->setIcon(ButtonIcon1);
        m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
        playBot();
        m[6-brancaI][brancaJ]->setIcon(ButtonIcon2);
        m[6-brancaI][brancaJ]->setIconSize(m[6-brancaI][brancaJ]->size());
        if(end()){
            game_end = 1;
            if(brancaI==pfinal[0][0] && brancaJ==pfinal[0][1])
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            else if(brancaI==pfinal[1][0] && brancaJ==pfinal[1][1])
                QMessageBox::information(this,"Game ended","Perdes-te!\n");
            else
                QMessageBox::information(this,"Game ended","Ganhas-te!\n");
            return;
        }
        turn = 0;
        game_start=0;
    }
}
