#ifndef PRODUTO_H
#define PRODUTO_H

#include <QWidget>
#include <QPushButton>
#include <vector>

namespace Ui {
class produto;
}

class produto : public QWidget
{
    Q_OBJECT

public:
    explicit produto(QWidget *parent = 0,QPushButton *b = 0);
    ~produto();

private:
    Ui::produto  *ui;
    QPushButton *back;

    int npretas;
    int nbrancas;
    int turn; //1=human, 2=computer
    int game_end;
    int game_start;
    int first_player;


    int max_depth;

    std::array< std::array<int, 9>, 9> board;

    void init();
    bool validMove(int i,int j);
    std::vector<std::pair<int,int> > possibleMoves();
    bool end();
    bool playHuman(int i,int j, int color);
    int heuristic();
    void playBot();
    void AlphaBeta();
    int min_value(int alfa, int beta, int depth);
    int max_value(int alfa, int beta, int depth);
};

#endif // RASTROS_H
