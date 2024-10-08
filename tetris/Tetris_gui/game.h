#ifndef GAME_H
#define GAME_H

#include "Board.h"

namespace model {

class Game {
private:
    Board board;
    //brickFactory brickFormation;
    int score;
    int level;
    int nbLineCleared;
//    int lineClearedForLevel;

public:
    explicit Game();
    Game(int row, int col);

    int lineClearedForLevel;
    void start(); //à effacer
    void startPersonalized(); //à effacer
    //brick* getRandomBrick() const;
    int clearAllLines();
    void moveBrickLeft();
    void moveBrickRight();
    void moveBrickDown();
    void rotateBrick();
    void undoRotateBrick();
    int drop();
    void updateScore(int clearedLines, int dropHeight);
    int getScore() const;
    int getLevel() const;
    void updateLevel(int maxLevel);
    int getLevelInterval();
    int getNbLineCleared() const;
    Board getBoard();
    bool updateGame();
    void setBoard(const Board &b);
    //void setLockedBrick();
};

}

#endif // GAME_H
