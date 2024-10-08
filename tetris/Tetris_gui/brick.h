#ifndef BRICK_H
#define BRICK_H

#include <vector>
#include <map>
#include "position.h"

namespace model {

class brick {
public:
    brick();
    virtual ~brick() {}
    void draw();
    void move(int rows, int column);
    std::vector<position> getPosition();
    void rotate();
    void undoRotate();
    bool active = true;

protected:
    int rotation;
    int rowOffset;
    int columOffset;
    int cols;
    int id;
    char fillChar;
    std::map<int, std::vector<position>> cases;
};

}

#endif // BRICK_H

