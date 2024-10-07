#include "position.h"

namespace model {

/**
 * @file position.cpp
 * @brief Implémentation des méthodes de la classe position
 */

/**
 * @brief Constructeur de la classe position.
 *
 * Initialise les coordonnées de la position avec les valeurs spécifiées.
 *
 * @param row La coordonnée de ligne.
 * @param column La coordonnée de colonne.
 */
position::position(int row, int column) : row(row), column(column) {}

/**
 * @brief Méthode pour obtenir la coordonnée de ligne.
 *
 * @return La coordonnée de ligne.
 */
int position::getRow() const {
    return row;
}

/**
 * @brief Méthode pour obtenir la coordonnée de colonne.
 *
 * @return La coordonnée de colonne.
 */
int position::getColumn() const {
    return column;
}

}
