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

private slots:
    void on_sair_2_clicked();


    void on_b00_clicked();
    void on_b01_clicked();
    void on_b02_clicked();
    void on_b03_clicked();
    void on_b04_clicked();
    void on_b10_clicked();
    void on_b11_clicked();
    void on_b12_clicked();
    void on_b13_clicked();
    void on_b14_clicked();
    void on_b15_clicked();
    void on_b20_clicked();
    void on_b21_clicked();
    void on_b22_clicked();
    void on_b23_clicked();
    void on_b24_clicked();
    void on_b25_clicked();
    void on_b26_clicked();
    void on_b30_clicked();
    void on_b31_clicked();
    void on_b32_clicked();
    void on_b33_clicked();
    void on_b34_clicked();
    void on_b35_clicked();
    void on_b36_clicked();
    void on_b37_clicked();
    void on_b40_clicked();
    void on_b41_clicked();
    void on_b42_clicked();
    void on_b43_clicked();
    void on_b44_clicked();
    void on_b45_clicked();
    void on_b46_clicked();
    void on_b47_clicked();
    void on_b48_clicked();
    void on_b50_clicked();
    void on_b51_clicked();
    void on_b52_clicked();
    void on_b53_clicked();
    void on_b54_clicked();
    void on_b55_clicked();
    void on_b56_clicked();
    void on_b57_clicked();
    void on_b60_clicked();
    void on_b61_clicked();
    void on_b62_clicked();
    void on_b63_clicked();
    void on_b64_clicked();
    void on_b65_clicked();
    void on_b66_clicked();
    void on_b70_clicked();
    void on_b71_clicked();
    void on_b72_clicked();
    void on_b73_clicked();
    void on_b74_clicked();
    void on_b75_clicked();
    void on_b80_clicked();
    void on_b81_clicked();
    void on_b82_clicked();
    void on_b83_clicked();
    void on_b84_clicked();

private:
    Ui::produto  *ui;
    QPushButton *back;
    QPushButton *m[9][9];

    std::array< std::array<int, 9>, 9> board;
    std::array< std::array<bool, 9>, 9> board2;
    int npretas;
    int nbrancas;
    int prodb; //score total das pretas
    int prodp; //score total das brancas
    int grupop; //grupos de pretas
    int grupob; //grupos de brancas
    std::vector<int> gruposp;
    std::vector<int> gruposb;
    int turn; //1=human, 2=computer
    int game_end;
    int game_start;
    int first_player;
    int nturn;

    int max_depth;

    void click(int i,int j);
    void init();
    bool validMove(int i,int j);
    std::vector<std::pair<int,int> > possibleMoves();
    bool end();
    bool playHuman(int i,int j, int color);
    int heuristic();
    std::pair<int,int> playBot();
    void AlphaBeta();
    int min_value(int alfa, int beta, int depth);
    int max_value(int alfa, int beta, int depth);
    void init_win();
    void change_color(int color,int i,int j);
    bool valid_move(int i, int j);
    int result();
    int bfs(std::pair<int, int> r, int color);
};

#endif // RASTROS_H
