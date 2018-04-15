#include "produto.h"
#include "ui_produto.h"

#include <queue>

produto::produto(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::produto)
{
    ui->setupUi(this);
    back = b;
    init_win();
    init();
}

produto::~produto()
{
    delete ui;
}

void produto::init_win()
{
    for(int i=0;i<5;i++) change_color(0,0,i);
    for(int i=0;i<6;i++) change_color(0,1,i);
    for(int i=0;i<7;i++) change_color(0,2,i);
    for(int i=0;i<8;i++) change_color(0,3,i);
    for(int i=0;i<9;i++) change_color(0,4,i);
    for(int i=0;i<8;i++) change_color(0,5,i);
    for(int i=0;i<7;i++) change_color(0,6,i);
    for(int i=0;i<6;i++) change_color(0,7,i);
    for(int i=0;i<5;i++) change_color(0,8,i);
    turn = 0;
    nturn=0;
    game_end=0;
    game_start = 1;
    first_player = 0;
}




void produto::on_sair_2_clicked()
{
    back->click();
}

void produto::click(int i, int j)
{
    if(!valid_move(i,j)) return;
    int play,color;
    if(ui->black->isChecked()){
        play = 1;
        color=2;
    }
    else{
        play =2;
        color=1;
    }
    playHuman(i,j,play);
    change_color(color,i,j);
    nturn++;

    std::pair<int,int> p;
    if(game_start && nturn==1){
        game_start = 0;
        nturn = 0;
        //joga o bot
        p = playBot();
        change_color(1,p.first,p.second);

        p = playBot();
        change_color(1,p.first,p.second);

    }
    else if(nturn>1){
        nturn = 0;
        //joga o bot
        game_start = 1;
        nturn = 0;
        //joga o bot
        p = playBot();
        change_color(1,p.first,p.second);

        p = playBot();
        change_color(1,p.first,p.second);

    }

}

void produto::init()
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

std::vector<std::pair<int, int> > produto::possibleMoves()
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

bool produto::valid_move(int i, int j)
{
    printf ("%d\n",board[i][j] );
    return board[i][j] == 0;
}

bool produto::end()
{
    if (nbrancas+npretas == 61)
        return true;
    else
        return false;
}

int produto::result() {
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

int produto::bfs (std::pair<int,int> r, int color) {
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

bool produto::playHuman(int i,int j, int color)
{
    if (!valid_move(i,j)) return false;
    board[i][j]=color; //1 preto, 2 branco
    if (color == 1)
        npretas++;
    else
        nbrancas++;
    return true;
}

std::pair<int,int> produto::playBot()
{
    //AlphaBeta();
    srand (time(NULL));
    std::vector<std::pair<int,int> > v = possibleMoves();
    int i = rand() % v.size();
    board[v[i].first][v[i].second]=1;
    return v[i];
}

























//0 clean
//1 yellow
//2 black
void produto::change_color(int color, int i, int j)
{
    switch(i*10+j){
    case 00:
        ui->b00->setAutoFillBackground(true);
        if(color == 0)
            ui->b00->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b00->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b00->setStyleSheet("background-color: black");
        return;
    case 01:
        if(color == 0)
            ui->b01->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b01->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b01->setStyleSheet("background-color: black");
        return;
    case 02:
        if(color == 0)
            ui->b02->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b02->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b02->setStyleSheet("background-color: black");
        return;
    case 03:
        if(color == 0)
            ui->b03->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b03->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b03->setStyleSheet("background-color: black");
        return;
    case 04:
        if(color == 0)
            ui->b04->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b04->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b04->setStyleSheet("background-color: black");
        return;

    case 10:
        if(color == 0)
            ui->b10->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b10->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b10->setStyleSheet("background-color: black");
        return;
    case 11:
        if(color == 0)
            ui->b11->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b11->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b11->setStyleSheet("background-color: black");
        return;
    case 12:
        if(color == 0)
            ui->b12->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b12->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b12->setStyleSheet("background-color: black");
        return;
    case 13:
        if(color == 0)
            ui->b13->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b13->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b13->setStyleSheet("background-color: black");
        return;
    case 14:
        if(color == 0)
            ui->b14->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b14->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b14->setStyleSheet("background-color: black");
        return;
    case 15:
        if(color == 0)
            ui->b15->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b15->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b15->setStyleSheet("background-color: black");
        return;

    case 20:
        if(color == 0)
            ui->b20->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b20->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b20->setStyleSheet("background-color: black");
        return;
    case 21:
        if(color == 0)
            ui->b21->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b21->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b21->setStyleSheet("background-color: black");
        return;
    case 22:
        if(color == 0)
            ui->b22->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b22->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b22->setStyleSheet("background-color: black");
        return;
    case 23:
        if(color == 0)
            ui->b23->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b23->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b23->setStyleSheet("background-color: black");
        return;
    case 24:
        if(color == 0)
            ui->b24->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b24->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b24->setStyleSheet("background-color: black");
        return;
    case 25:
        if(color == 0)
            ui->b25->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b25->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b25->setStyleSheet("background-color: black");
        return;
    case 26:
        if(color == 0)
            ui->b26->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b26->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b26->setStyleSheet("background-color: black");
        return;

    case 30:
        if(color == 0)
            ui->b30->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b30->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b30->setStyleSheet("background-color: black");
        return;
    case 31:
        if(color == 0)
            ui->b31->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b31->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b31->setStyleSheet("background-color: black");
        return;
    case 32:
        if(color == 0)
            ui->b32->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b32->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b32->setStyleSheet("background-color: black");
        return;
    case 33:
        if(color == 0)
            ui->b33->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b33->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b33->setStyleSheet("background-color: black");
        return;
    case 34:
        if(color == 0)
            ui->b34->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b34->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b34->setStyleSheet("background-color: black");
        return;
    case 35:
        if(color == 0)
            ui->b35->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b35->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b35->setStyleSheet("background-color: black");
        return;
    case 36:
        if(color == 0)
            ui->b36->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b36->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b36->setStyleSheet("background-color: black");
        return;
    case 37:
        if(color == 0)
            ui->b37->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b37->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b37->setStyleSheet("background-color: black");
        return;

    case 40:
        if(color == 0)
            ui->b40->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b40->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b40->setStyleSheet("background-color: black");
        return;
    case 41:
        if(color == 0)
            ui->b41->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b41->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b41->setStyleSheet("background-color: black");
        return;
    case 42:
        if(color == 0)
            ui->b42->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b42->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b42->setStyleSheet("background-color: black");
        return;
    case 43:
        if(color == 0)
            ui->b43->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b43->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b43->setStyleSheet("background-color: black");
        return;
    case 44:
        if(color == 0)
            ui->b44->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b44->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b44->setStyleSheet("background-color: black");
        return;
    case 45:
        if(color == 0)
            ui->b45->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b45->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b45->setStyleSheet("background-color: black");
        return;
    case 46:
        if(color == 0)
            ui->b46->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b46->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b46->setStyleSheet("background-color: black");
        return;
    case 47:
        if(color == 0)
            ui->b47->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b47->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b47->setStyleSheet("background-color: black");
        return;
    case 48:
        if(color == 0)
            ui->b48->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b48->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b48->setStyleSheet("background-color: black");
        return;

    case 50:
        if(color == 0)
            ui->b50->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b50->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b50->setStyleSheet("background-color: black");
        return;
    case 51:
        if(color == 0)
            ui->b51->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b51->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b51->setStyleSheet("background-color: black");
        return;
    case 52:
        if(color == 0)
            ui->b52->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b52->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b52->setStyleSheet("background-color: black");
        return;
    case 53:
        if(color == 0)
            ui->b53->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b53->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b53->setStyleSheet("background-color: black");
        return;
    case 54:
        if(color == 0)
            ui->b54->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b54->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b54->setStyleSheet("background-color: black");
        return;
    case 55:
        if(color == 0)
            ui->b55->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b55->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b55->setStyleSheet("background-color: black");
        return;
    case 56:
        if(color == 0)
            ui->b56->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b56->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b56->setStyleSheet("background-color: black");
        return;
    case 57:
        if(color == 0)
            ui->b57->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b57->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b57->setStyleSheet("background-color: black");
        return;

    case 60:
        if(color == 0)
            ui->b60->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b60->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b60->setStyleSheet("background-color: black");
        return;
    case 61:
        if(color == 0)
            ui->b61->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b61->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b61->setStyleSheet("background-color: black");
        return;
    case 62:
        if(color == 0)
            ui->b62->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b62->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b62->setStyleSheet("background-color: black");
        return;
    case 63:
        if(color == 0)
            ui->b63->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b63->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b63->setStyleSheet("background-color: black");
        return;
    case 64:
        if(color == 0)
            ui->b64->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b64->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b64->setStyleSheet("background-color: black");
        return;
    case 65:
        if(color == 0)
            ui->b65->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b65->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b65->setStyleSheet("background-color: black");
        return;
    case 66:
        if(color == 0)
            ui->b66->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b66->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b66->setStyleSheet("background-color: black");
        return;

    case 70:
        if(color == 0)
            ui->b70->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b70->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b70->setStyleSheet("background-color: black");
        return;
    case 71:
        if(color == 0)
            ui->b71->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b71->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b71->setStyleSheet("background-color: black");
        return;
    case 72:
        if(color == 0)
            ui->b72->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b72->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b72->setStyleSheet("background-color: black");
        return;
    case 73:
        if(color == 0)
            ui->b73->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b73->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b73->setStyleSheet("background-color: black");
        return;
    case 74:
        if(color == 0)
            ui->b74->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b74->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b74->setStyleSheet("background-color: black");
        return;
    case 75:
        if(color == 0)
            ui->b75->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b75->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b75->setStyleSheet("background-color: black");
        return;

    case 80:
        if(color == 0)
            ui->b80->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b80->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b80->setStyleSheet("background-color: black");
        return;
    case 81:
        if(color == 0)
            ui->b81->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b81->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b81->setStyleSheet("background-color: black");
        return;
    case 82:
        if(color == 0)
            ui->b82->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b82->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b82->setStyleSheet("background-color: black");
        return;
    case 83:
        if(color == 0)
            ui->b83->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b83->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b83->setStyleSheet("background-color: black");
        return;
    case 84:
        if(color == 0)
            ui->b84->setStyleSheet("background-color: white");
        if(color == 1)
            ui->b84->setStyleSheet("background-color: yellow");
        if(color == 2)
            ui->b84->setStyleSheet("background-color: black");
        return;
    }
}

void produto::on_b00_clicked()
{
    click(0,0);
}
void produto::on_b01_clicked()
{
    click(0,1);
}
void produto::on_b02_clicked()
{
    click(0,2);
}
void produto::on_b03_clicked()
{
    click(0,3);
}
void produto::on_b04_clicked()
{
    click(0,4);
}
void produto::on_b10_clicked()
{
    click(1,0);
}
void produto::on_b11_clicked()
{
    click(1,1);
}
void produto::on_b12_clicked()
{
    click(1,2);
}
void produto::on_b13_clicked()
{
    click(1,3);
}
void produto::on_b14_clicked()
{
    click(1,4);
}
void produto::on_b15_clicked()
{
    click(1,5);
}
void produto::on_b20_clicked()
{
    click(2,0);
}
void produto::on_b21_clicked()
{
    click(2,1);
}
void produto::on_b22_clicked()
{
    click(2,2);
}
void produto::on_b23_clicked()
{
    click(2,3);
}
void produto::on_b24_clicked()
{
    click(2,4);
}
void produto::on_b25_clicked()
{
    click(2,5);
}
void produto::on_b26_clicked()
{
    click(2,6);
}
void produto::on_b30_clicked()
{
    click(3,0);
}
void produto::on_b31_clicked()
{
    click(3,1);
}
void produto::on_b32_clicked()
{
    click(3,2);
}
void produto::on_b33_clicked()
{
    click(3,3);
}
void produto::on_b34_clicked()
{
    click(3,4);
}
void produto::on_b35_clicked()
{
    click(3,5);
}
void produto::on_b36_clicked()
{
    click(3,6);
}
void produto::on_b37_clicked()
{
    click(3,7);
}
void produto::on_b40_clicked()
{
    click(4,0);
}
void produto::on_b41_clicked()
{
    click(4,1);
}
void produto::on_b42_clicked()
{
    click(4,2);
}
void produto::on_b43_clicked()
{
    click(4,3);
}
void produto::on_b44_clicked()
{
    click(4,4);
}
void produto::on_b45_clicked()
{
    click(4,5);
}
void produto::on_b46_clicked()
{
    click(4,6);
}
void produto::on_b47_clicked()
{
    click(4,7);
}
void produto::on_b48_clicked()
{
    click(4,8);
}
void produto::on_b50_clicked()
{
    click(5,0);
}
void produto::on_b51_clicked()
{
    click(5,1);
}
void produto::on_b52_clicked()
{
    click(5,2);
}
void produto::on_b53_clicked()
{
    click(5,3);
}
void produto::on_b54_clicked()
{
    click(5,4);
}
void produto::on_b55_clicked()
{
    click(5,5);
}
void produto::on_b56_clicked()
{
    click(5,6);
}
void produto::on_b57_clicked()
{
    click(5,7);
}
void produto::on_b60_clicked()
{
    click(6,0);
}
void produto::on_b61_clicked()
{
    click(6,1);
}
void produto::on_b62_clicked()
{
    click(6,2);
}
void produto::on_b63_clicked()
{
    click(6,3);
}
void produto::on_b64_clicked()
{
    click(6,4);
}
void produto::on_b65_clicked()
{
    click(6,5);
}
void produto::on_b66_clicked()
{
    click(6,6);
}
void produto::on_b70_clicked()
{
    click(7,0);
}
void produto::on_b71_clicked()
{
    click(7,1);
}
void produto::on_b72_clicked()
{
    click(7,2);
}
void produto::on_b73_clicked()
{
    click(7,3);
}
void produto::on_b74_clicked()
{
    click(7,4);
}
void produto::on_b75_clicked()
{
    click(7,5);
}
void produto::on_b80_clicked()
{
    click(8,0);
}
void produto::on_b81_clicked()
{
    click(8,1);
}
void produto::on_b82_clicked()
{
    click(8,2);
}
void produto::on_b83_clicked()
{
    click(8,3);
}
void produto::on_b84_clicked()
{
    click(8,4);
}


