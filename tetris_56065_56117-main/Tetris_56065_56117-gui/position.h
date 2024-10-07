#ifndef POSITION_H
#define POSITION_H

namespace model {

class position {
public:
    // Constructeur
    position(int row, int column);

    // Méthodes publiques
    int getRow() const;
    int getColumn() const;

private:
    // Attributs privés
    int row;
    int column;
};

}

#endif // POSITION_H

