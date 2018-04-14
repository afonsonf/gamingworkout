#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Semaforo;
}

class Semaforo : public QWidget
{
    Q_OBJECT

public:
    explicit Semaforo(QWidget *parent = 0,QPushButton *back = 0);
    ~Semaforo();

    void init_win();
    void initGame();

    void but_click(int i, int j);

    std::array< std::array<char, 4>, 3> getBoard();
    int getTurn();
    int getLastMoveX();
    int getLastMoveY();

    bool validMove(int moveY, int moveX);
    std::vector< std::pair<int, int> > possibleMoves();
    void playHuman(int moveY, int moveX);
    std::pair<int, int> playBot();
    std::pair<int, int> chooseMove();
    void updateBoard(int moveY, int moveX);
    bool checkGameOver();

private slots:
    void on_pushButton_clicked();

    void on_sair_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Semaforo *ui;

    std::array< std::array<char, 4>, 3> board;
    int turn; //1=human, 2=computer
    int lastMoveX;
    int lastMoveY;
    QPushButton *back;

};

#endif // SEMAFORO_H
