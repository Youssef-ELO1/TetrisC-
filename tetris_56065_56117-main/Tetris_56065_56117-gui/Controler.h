#ifndef CONTROLER_H
#define CONTROLER_H

#include "Board.h"
#include "game.h"
#include "view.h"


namespace controler {

class Controler
{
public:
    Controler(model::Game &b,view::View& v);

    void draw();
    void handleInput(int keyPressed=0);
    int getKeyPressed();
    void updateGame();
    bool isGameOver();
    void GameOver();
    bool winner();
    int getScore() const;
    int getLevel() const;
    int getNbLineCleared() const;
    int getInput();
    void play();
    model::Board getBoard();

private:
    model::Game& board;
    view::View view;
    bool gameOver;
};

}

#endif // CONTROLER_H
