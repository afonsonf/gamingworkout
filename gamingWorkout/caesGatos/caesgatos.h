#ifndef CAESGATOS_H
#define CAESGATOS_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class CaesGatos;
}

class CaesGatos : public QWidget
{
    Q_OBJECT

public:
    explicit CaesGatos(QWidget *parent = 0,QPushButton *back = 0);

    ~CaesGatos();

private slots:
    void on_sair_clicked();

private:
    Ui::CaesGatos *ui;
    QPushButton *back;
    QPushButton *m[8][8];
    void init_win();
    void but_click(int i, int j);

    int game_end;
    int game_start;
    int first_player;
    int turn;
    int board[100]; // 10*coluna + linha
    int bestMove;
    int depthmax;

    bool end();
    std::vector<int> possMoves(int player);
    bool playHuman(int move);
    int playBot();
    bool validMove(int player, int move);
    void initGame();
    int ABminValue(int maxDistanceDepth, int alpha, int beta);
    int ABmaxValue(int maxDistanceDepth, int alpha, int beta);
    int alphabetaDecision(int maxDistanceDepth);
};

#endif // CAESGATOS_H
