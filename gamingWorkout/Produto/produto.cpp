#include "produto.h"
#include "ui_produto.h"

produto::produto(QWidget *parent,QPushButton *b) :
    QWidget(parent),
    ui(new Ui::rastros)
{
    ui->setupUi(this);
    back = b;
}

produto::~produto()
{
    delete ui;
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
	std::vector<std::pair<int,int> > v;
	for (int i=0;i<9;i++) {
		for (int j=0;j<9;j++) {
			if (board[i][j]==0)
				p.push_back(std::make_pair(i,j));
		}
	}
}

bool rastros::valid_move(int i, int j)
{
    return board[i][j] == 0;
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
	if (!valid_move(i,j)) return false;
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