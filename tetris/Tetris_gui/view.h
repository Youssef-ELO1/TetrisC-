#ifndef VIEW_H
#define VIEW_H

#include "Board.h"
#include "game.h"

namespace view {

class View {
public:
    explicit View();
    View(model::Game&);
    void setBoard(const model::Board& b);
    void setBoard(const model::Game& g);
    void printBienvenu();
    //void printBoard(const model::Game&);
    void printBoard();
    void printScore(int score);
    void printGameOver();
    //int getInput();
    void printLevel(int level);
    void printWinner();
    void printBoardperso();
    void printNbLineCleared(int nbLineCleared);
    void printInputOptions();
    void printInvalidInputMessage();
    void printInputResult(int input);
private:
    model::Game& model;
};

}

#endif // VIEW_H
