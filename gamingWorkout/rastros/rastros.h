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

private slots:
    void on_sair_clicked();

    void on_new_game_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    int nturn;
    Ui::rastros *ui;
    QPushButton *back;
    QPushButton *m[7][7];
    int game_end;
    int game_start;
    int first_player;
    int dif;

    int brancaI;
    int brancaJ;
    int pfinal[2][2];
    int turn;
    int best_play[2];

    int max_depth;

    std::array< std::array<int, 7>, 7> board;

    void init();
    bool valid_move(int i,int j);
    std::vector<std::pair<int,int> > possible_moves(int ix,int jx);
    bool end();
    bool playHuman(int i,int j);
    int heuristic();
    void playBot();
    void AlphaBeta();
    int min_value(int alfa, int beta, int depth);
    int max_value(int alfa, int beta, int depth);
    void init_win();
    void but_click(int i, int j);
};

#endif // RASTROS_H
