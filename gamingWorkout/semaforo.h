#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <QWidget>

namespace Ui {
class Semaforo;
}

class Semaforo : public QWidget
{
    Q_OBJECT

public:
    explicit Semaforo(QWidget *parent = 0);
    Semaforo();
    Semaforo(int turn);
    Semaforo(Semaforo& parent, int moveX, int moveY);
    ~Semaforo();

    std::array< std::array<char, 4>, 3> getBoard();
    int getTurn();
    int getLastMoveX();
    int getLastMoveY();

    bool validMove(int moveX, int moveY);
    std::vector< std::array<int, 2> > possibleMoves();

private:
    Ui::Semaforo *ui;

    std::array< std::array<char, 4>, 3> board;
    int turn; //1=human, 2=computer
    int lastMoveX;
    int lastMoveY;
};

#endif // SEMAFORO_H
