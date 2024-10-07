#include "brick.h"
#include <iostream>

namespace model {

using namespace std;

/**
 * @file brick.cpp
 * @brief Implémentation des méthodes de la classe Brick
 */

/**
 * @brief Constructeur de la classe brick.
 *
 * Initialise les attributs de la brique.
 */
brick::brick() {
    rotation = 0;
    fillChar = 'X';
    rowOffset = 0;
    columOffset = 0;
}

/**
 * @brief Méthode pour dessiner la brique.
 *
 * Affiche le caractère de remplissage de la brique sur la sortie standard.
 */
void brick::draw() {
    cout << fillChar << " ";
}

/**
 * @brief Méthode pour obtenir les positions des cases de la brique.
 *
 * @return Un vecteur contenant les positions des cases de la brique après avoir appliqué les décalages.
 */
vector<position> brick::getPosition() {
    vector<position> tiles = cases[rotation];
    vector<position> movedtiles;
    for(position item: tiles) {
        position newPos = position(item.getRow() + rowOffset, item.getColumn() + columOffset);
        movedtiles.push_back(newPos);
    }
    return movedtiles;
}

/**
 * @brief Méthode pour déplacer la brique.
 *
 * Cette méthode déplace la brique selon le nombre de lignes et de colonnes spécifié.
 *
 * @param rows Le nombre de lignes à déplacer.
 * @param columns Le nombre de colonnes à déplacer.
 */
void brick::move(int rows, int columns) {
    rowOffset += rows;
    columOffset += columns;
}

/**
 * @brief Méthode pour faire tourner la brique dans le sens horaire.
 *
 * Incrémente la rotation de la brique. Si la rotation dépasse le nombre de cas possibles,
 * elle revient au premier cas.
 */
void brick::rotate() {
    rotation++;
    if(rotation == (int)cases.size()) {
        rotation = 0;
    }
}

/**
 * @brief Méthode pour annuler la rotation de la brique.
 *
 * Décrémente la rotation de la brique. Si la rotation devient inférieure à zéro,
 * elle revient au dernier cas possible.
 */
void brick::undoRotate() {
    rotation--;
    if(rotation == -1) {
        rotation = cases.size() - 1;
    }
}

}

