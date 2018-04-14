#ifndef RASTROS_H
#define RASTROS_H

#include <QWidget>
#include <QPushButton>
#include <vector>

namespace Ui {
class rastros;
}

class rastros : public QWidget
{
    Q_OBJECT

public:
    explicit rastros(QWidget *parent = 0,QPushButton *b = 0);
    ~rastros();

private:
    Ui::rastros *ui;
    QPushButton *back;

    int brancaI;
    int brancaJ;
    int pfinal[2][2];
    int turn;

    int max_depth;

    std::array< std::array<int, 7>, 7> board;

    void init();
    bool valid_move(int i,int j);
    std::vector<std::pair<int,int> > possible_moves(int ix,int jx);
    bool end();
    bool playHuman(int i,int j);
    int heuristic();
};

#endif // RASTROS_H
