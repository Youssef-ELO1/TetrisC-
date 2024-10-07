#ifndef BRICKS_H
#define BRICKS_H

#include "brick.h"

namespace model {

class brickFactory {
public:
    brickFactory(int cols);
    brick * createRandomBrick() const;
    int getCol() const;

private:
    int cols;
};


class Lbrick : public brick {
public:
    Lbrick(int cols);
};

class Jbrick : public brick {
public:
    Jbrick(int cols);
};

class Ibrick : public brick {
public:
    Ibrick(int cols);
};

class Obrick : public brick {
public:
    Obrick(int cols);
};

class Sbrick : public brick {
public:
    Sbrick(int cols);
};

class Tbrick : public brick {
public:
    Tbrick(int cols);
};

class Zbrick : public brick {
public:
    Zbrick(int cols);
};

}

#endif
