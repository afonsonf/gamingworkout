/*#ifndef AVANCO_H
#define AVANCO_H

#include <QWidget>

namespace Ui {
class avanco;
}

class avanco : public QWidget
{
    Q_OBJECT

public:
    explicit avanco(QWidget *parent = 0);
    ~avanco();

    void init_win();
    void initGame();

    void but_click(int i, int j);

    std::array< std::array<char, 7>, 7> getBoard();
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

private:
    Ui::avanco *ui;

    std::array< std::array<int, 7>, 7> board;
    int turn; //1=human, 2=computer
    int lastMoveX;
    int lastMoveY;
    QPushButton *back;
    QPushButton *m[7][7];
    int game_end;
    int game_start;
    int first_player;
};

#endif // AVANCO_H
*/
