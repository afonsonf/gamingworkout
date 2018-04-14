#include "produto.h"
#include "ui_produto.h"

produto::produto(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::produto)
{
    ui->setupUi(this);
    back = b;
}

produto::~produto()
{
    delete ui;
}
/*
void produto::init_win()
{
    ui->gridLayout->setSpacing(5);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            m[i][j] = new QPushButton;
            m[i][j]->setFixedHeight(200);
            m[i][j]->setFixedWidth(200);
            if (std::abs(i-j)<5){
                connect(m[i][j],&QPushButton::clicked, [=]() {
                    but_click(i,j);
                });
                m[i][j]->setStyleSheet("background-color: white");
            }
            else
                 m[i][j]->setStyleSheet("background-color: none");
            ui->gridLayout->addWidget(m[i][j],i,j);
        }
    }
    turn = 2;
    game_end=0;
    game_start = 1;
    first_player = 2;
}*/

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
	std::vector<std::pair<int,int> > v;
	for (int i=0;i<9;i++) {
		for (int j=0;j<9;j++) {
			if (board[i][j]==0)
                v.push_back(std::make_pair(i,j));
		}
	}

    return v;
}

bool produto::validMove(int i, int j)
{
    return (this->board[i][j] == 0);
}

bool produto::end() 
{
	if (nbrancas+npretas == 61)
		return true;
	else
		return false;
}

bool produto::playHuman(int i,int j, int color)
{
    if (!validMove(i,j)) return false;
	board[i][j]=color;
	return true;
}

void produto::playBot()
{
    AlphaBeta();
    board[brancaI][brancaJ] = 1;
    brancaI = best_play[0];
    brancaJ = best_play[1];
}
