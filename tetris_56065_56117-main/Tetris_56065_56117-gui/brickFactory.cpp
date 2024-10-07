#include "brickFactory.h"
#include <ctime>
#include <cstdlib>
#include <set>

namespace model {

using namespace std;

// Définir le nombre total de types de briques
const int NUM_BRICK_TYPES = 7;

brickFactory::brickFactory(int cols):cols(cols){}

int brickFactory::getCol() const{
    return cols;
}
/**
 * @brief Méthode pour créer une brique aléatoire.
 *
 * Crée une brique aléatoire en utilisant la fonction rand(). Cette méthode garantit que chaque type de brique est créé exactement une fois avant de recommencer le cycle.
 *
 * @return Un pointeur vers la brique créée.
 */
brick* brickFactory::createRandomBrick() const {
    // Déclaration d'un ensemble pour suivre les types de briques déjà créées
    static set<int> createdBrickTypes;

    // Si toutes les briques ont été créées au moins une fois, réinitialiser l'ensemble
    if (createdBrickTypes.size() == NUM_BRICK_TYPES) {
        createdBrickTypes.clear();
    }

    srand(time(0)); // Initialisation du générateur de nombres aléatoires

    // Déclaration d'une variable pour stocker le type de brique sélectionné
    int random;
    do {
        // Générer un nombre aléatoire entre 0 et 6 (7 types de briques au total)
        random = rand() % 7;
    } while (createdBrickTypes.count(random) > 0); // Vérifier si ce type de brique a déjà été créé

    // Ajouter le type de brique sélectionné à l'ensemble des types créés
    createdBrickTypes.insert(random);
    int cols=getCol();
    // Retourner la brique correspondante en fonction du type sélectionné
    switch(random) {
    case 0:
        return new Lbrick(cols);
    case 1:
        return new Jbrick(cols);
    case 2:
        return new Ibrick(cols);
    case 3:
        return new Obrick(cols);
    case 4:
        return new Sbrick(cols);
    case 5:
        return new Tbrick(cols);
    case 6:
        return new Zbrick(cols);
    default:
        return nullptr;
    }
}



/**
 * @brief Constructeur de la classe Lbrick.
 *
 * Initialise une brique de type L avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (0,2), (1,0), (1,1), (1,2)
 * - Rotation 1 : positions (0,1), (1,1), (2,1), (2,2)
 * - Rotation 2 : positions (1,0), (1,1), (1,2), (2,0)
 * - Rotation 3 : positions (0,0), (0,1), (1,1), (2,1)
 */
Lbrick::Lbrick(int col) {
    cols=col;
    id = 1;
    cases[0] = {position(0,2), position(1,0), position(1,1), position(1,2)};
    cases[1] = {position(0,1), position(1,1), position(2,1), position(2,2)};
    cases[2] = {position(1,0), position(1,1), position(1,2), position(2,0)};
    cases[3] = {position(0,0), position(0,1), position(1,1), position(2,1)};
    move(0,(cols/2)-2);
}

/**
 * @brief Constructeur de la classe Jbrick.
 *
 * Initialise une brique de type J avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (0,0), (1,0), (1,1), (1,2)
 * - Rotation 1 : positions (0,1), (0,2), (1,1), (2,1)
 * - Rotation 2 : positions (1,0), (1,1), (1,2), (2,2)
 * - Rotation 3 : positions (0,1), (1,1), (2,0), (2,1)
 */
Jbrick::Jbrick(int col) {
    cols=col;
    id = 2;
    cases[0] = {position(0,0), position(1,0), position(1,1), position(1,2)};
    cases[1] = {position(0,1), position(0,2), position(1,1), position(2,1)};
    cases[2] = {position(1,0), position(1,1), position(1,2), position(2,2)};
    cases[3] = {position(0,1), position(1,1), position(2,0), position(2,1)};
    move(0,(cols/2)-2);
}

/**
 * @brief Constructeur de la classe Ibrick.
 *
 * Initialise une brique de type I avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (1,0), (1,1), (1,2), (1,3)
 * - Rotation 1 : positions (0,2), (1,2), (2,2), (3,2)
 * - Rotation 2 : positions (2,0), (2,1), (2,2), (2,3)
 * - Rotation 3 : positions (0,1), (1,1), (2,1), (3,1)
 */
Ibrick::Ibrick(int col) {
    cols=col;
    id = 3;
    cases[0] = {position(1,0), position(1,1), position(1,2), position(1,3)};
    cases[1] = {position(0,2), position(1,2), position(2,2), position(3,2)};
    cases[2] = {position(2,0), position(2,1), position(2,2), position(2,3)};
    cases[3] = {position(0,1), position(1,1), position(2,1), position(3,1)};
    move(-1,(cols/2)-2);
}

/**
 * @brief Constructeur de la classe Obrick.
 *
 * Initialise une brique de type O avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (0,0), (0,1), (1,0), (1,1)
 */
Obrick::Obrick(int col) {
    cols=col;
    id = 4;
    cases[0] = {position(0,0), position(0,1), position(1,0), position(1,1)};
    move(0,(cols/2)-2);
}

/**
 * @brief Constructeur de la classe Sbrick.
 *
 * Initialise une brique de type S avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (0,1), (0,2), (1,0), (1,1)
 * - Rotation 1 : positions (0,1), (1,1), (1,2), (2,2)
 * - Rotation 2 : positions (1,1), (1,2), (2,0), (2,1)
 * - Rotation 3 : positions (0,0), (1,0), (1,1), (2,1)
 */
Sbrick::Sbrick(int col) {
    cols=col;
    id = 5;
    cases[0] = {position(0,1), position(0,2), position(1,0), position(1,1)};
    cases[1] = {position(0,1), position(1,1), position(1,2), position(2,2)};
    cases[2] = {position(1,1), position(1,2), position(2,0), position(2,1)};
    cases[3] = {position(0,0), position(1,0), position(1,1), position(2,1)};
    move(0,(cols/2)-2);
}

/**
 * @brief Constructeur de la classe Tbrick.
 *
 * Initialise une brique de type T avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (0,1), (1,0), (1,1), (1,2)
 * - Rotation 1 : positions (0,1), (1,1), (1,2), (2,1)
 * - Rotation 2 : positions (1,0), (1,1), (1,2), (2,1)
 * - Rotation 3 : positions (0,1), (1,0), (1,1), (2,1)
 */
Tbrick::Tbrick(int col) {
    cols=col;
    id = 6;
    cases[0] = {position(0,1), position(1,0), position(1,1), position(1,2)};
    cases[1] = {position(0,1), position(1,1), position(1,2), position(2,1)};
    cases[2] = {position(1,0), position(1,1), position(1,2), position(2,1)};
    cases[3] = {position(0,1), position(1,0), position(1,1), position(2,1)};
    move(0,(cols/2)-2);
}

/**
 * @brief Constructeur de la classe Zbrick.
 *
 * Initialise une brique de type Z avec ses configurations de cases pour chaque rotation.
 *
 * @details Les configurations de cases sont définies comme suit :
 * - Rotation 0 : positions (0,0), (0,1), (1,1), (1,2)
 * - Rotation 1 : positions (0,2), (1,1), (1,2), (2,1)
 * - Rotation 2 : positions (1,0), (1,1), (2,1), (2,2)
 * - Rotation 3 : positions (0,1), (1,0), (1,1), (2,0)
 */
Zbrick::Zbrick(int col) {
    cols=col;
    id = 7;
    cases[0] = {position(0,0), position(0,1), position(1,1), position(1,2)};
    cases[1] = {position(0,2), position(1,1), position(1,2), position(2,1)};
    cases[2] = {position(1,0), position(1,1), position(2,1), position(2,2)};
    cases[3] = {position(0,1), position(1,0), position(1,1), position(2,0)};
    move(0,(cols/2)-2);
}

}


