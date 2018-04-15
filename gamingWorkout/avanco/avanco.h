#ifndef AVANCO_H
#define AVANCO_H

#include <vector>

class avanco
{

public:
    avanco();
    void initGame();

    bool validMove(int oldY, int oldX, int newY, int newX);
    std::vector< std::pair<int, int> > possibleMoves(int i,int j);
    void playHuman(int Xnow, int Ynow,int moveY, int moveX);
    std::pair<int, int> playBot();
    std::pair<int, int> chooseMove();
    int checkGameOver();

private:

    int board[7][7];
    int turn; //0=human, 1=computer
    int lastMoveX;
    int lastMoveY;
    int game_end;
    int game_start;
    int first_player;
};

#endif // AVANCO_H