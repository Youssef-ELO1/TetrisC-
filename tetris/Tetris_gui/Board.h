#ifndef BOARD_H
#define BOARD_H

#include "position.h"
#include "brick.h"
#include "brickFactory.h"
#include <QPainter>

namespace model {

/**
 * @brief Classe représentant le plateau de jeu.
 */
class Board{
private:
    // Attributs privés
    brickFactory brickFormation; //game (à voir par rapport au currentBrick)
    std::vector<std::vector<int>> board;

    int cellSize;
    brick* currentBrick;

public:
    // Constructeurs
    explicit Board();
    Board(int row, int col);
    int rowsNum;
    int colsNum;
    // Méthodes publiques
    void initialise();
    bool isCasesOut(const position & pos);
    brick* getRandomBrick() const; //game mais pas encore sûr
    brick* getCurrentBrick() const;
    void setNewRandomCurrentBrick();
    void setLockedBrick(); //game mais pas encore sûr
    bool isCasesEmpty(const position & pos);
    bool isPosBrickEmpty();
    int getRowsNum() const;
    int getColsNum() const;
    int getBoardValue(int row, int column) const;
    bool isBrickOut();
    std::vector<position> getCurrentBrickPos() const;
    bool isBrickBottom();
    bool isPosistionInsideBrick(int row, int col);
    void clearLine(int row);
    bool rowFull(int row);
    void moveDownLine(int row, int rowsNum);
    void setCurrentBrickToNull();
    std::vector<std::vector<int>> getBoard();
    void setBoard(const Board &board);
    void draw(QPainter& painter);// TEST AJOUT
};

}

#endif // BOARD_H

