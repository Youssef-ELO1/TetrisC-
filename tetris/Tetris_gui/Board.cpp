#include "Board.h"
#include "brickFactory.h"
#include <algorithm>
#include <QPainter>

namespace model {

using namespace std;


/**
 * @brief Constructeur par défaut de la classe Board.
 *
 * Initialise les membres de la classe, crée le tableau de jeu avec des dimensions par défaut,
 * initialise le tableau avec des valeurs par défaut, obtient une nouvelle brique aléatoire,
 * initialise le score et le niveau et le nombre de ligne effacé.
 */
Board::Board() : brickFormation(10), rowsNum(20), colsNum(10), currentBrick(getRandomBrick())
{
    initialise();
}


/**
 * @brief Constructeur surchargé de la classe Board.
 *
 * Initialise les membres de la classe avec les dimensions spécifiées, crée le tableau de jeu
 * avec les dimensions données, initialise le tableau avec des valeurs par défaut, obtient une
 * nouvelle brique aléatoire, initialise le score et le niveau et le nombre de ligne effacé.
 *
 * @param row Le nombre de lignes du tableau.
 * @param col Le nombre de colonnes du tableau.
 */
Board::Board(int row,int col): brickFormation(col), rowsNum(row), colsNum(col), currentBrick(getRandomBrick())
{
    initialise();
}


/**
 * @brief Obtient une brique aléatoire.
 *
 * Cette méthode retourne une brique aléatoire à partir de la classe BrickFactory.
 *
 * @return Un pointeur vers la brique aléatoire créée.
 */
brick* Board::getRandomBrick() const {
    return brickFormation.createRandomBrick();
}

/**
 * @brief Obtient la valeur contenue dans le tableau à une position donnée.
 *
 * Cette méthode retourne la valeur contenue dans le tableau à la position spécifiée par la ligne et la colonne.
 *
 * @param row L'indice de la ligne dans le tableau.
 * @param column L'indice de la colonne dans le tableau.
 * @return La valeur contenue dans le tableau à la position spécifiée.
 */
int Board::getBoardValue(int row, int column) const {
    return board[row][column];
}

/**
 * @brief Obtient la brique actuelle.
 *
 * Cette méthode retourne la brique actuelle en jeu.
 *
 * @return Un pointeur vers la brique actuelle.
 */
brick* Board::getCurrentBrick() const {
    return currentBrick;
}

/**
 * @brief Définit une nouvelle brique aléatoire comme brique actuelle.
 *
 * Cette méthode génère une nouvelle brique aléatoire et la définit comme brique actuelle.
 */
void Board::setNewRandomCurrentBrick() {
    currentBrick = getRandomBrick();
}

/**
 * @brief Initialise le plateau de jeu.
 *
 * Cette méthode initialise le plateau de jeu avec les dimensions spécifiées.
 * Chaque élément du tableau est initialisé à zéro.
 */
void Board::initialise() {
    board.resize(rowsNum);

    for(int row = 0; row < rowsNum; row++) {
        board[row].resize(colsNum, 0);
    }
}



/**
 * @brief Vérifie si une position donnée est en dehors des limites du tableau.
 *
 * Cette méthode vérifie si les coordonnées spécifiées sont en dehors des limites du tableau.
 *
 * @param pos La position à vérifier.
 * @return true si la position est en dehors des limites du tableau, sinon false.
 */
bool Board::isCasesOut(const position & pos) {
    return (pos.getRow() < 0 || pos.getRow() >= rowsNum || pos.getColumn() < 0 || pos.getColumn() >= colsNum);
}



/**
 * @brief Méthode pour marquer la brique actuelle comme verrouillée dans le tableau.
 *
 * Récupère les positions de la brique actuelle et met à jour le tableau en marquant
 * les cases correspondantes comme verrouillées. Ensuite, elle appelle la méthode
 * ClearAllLines() pour effacer les lignes complètes et mettre à jour le score.
 */
void Board::setLockedBrick() {
    for(const auto& p : currentBrick->getPosition()) {
        board[p.getRow()][p.getColumn()] = 1;
    }
}


/**
 * @brief Vérifie si une position est vide sur le plateau de jeu.
 *
 * Cette méthode vérifie si la case spécifiée par la position donnée est vide sur le plateau de jeu.
 * Une case est considérée comme vide si sa valeur dans le tableau de jeu est égale à 0.
 *
 * @param pos La position à vérifier.
 * @return true si la case est vide, sinon false.
 */
bool Board::isCasesEmpty(const position & pos) {
    return (board[pos.getRow()][pos.getColumn()] == 0);
}

/**
 * @brief Méthode pour vérifier si une ligne du tableau est complète.
 *
 * Parcourt la ligne spécifiée et vérifie si toutes les cases sont remplies.
 *
 * @param row L'indice de ligne à vérifier.
 * @return Vrai si la ligne est complète, sinon faux.
 */
bool Board::rowFull(int row) {
    //MODIFICATION FAITE
    return all_of(board[row].begin(), board[row].end(), [](int value) {
        return value != 0;
    });
}

/**
 * @brief Méthode pour effacer une ligne du tableau.
 *
 * Parcourt la ligne spécifiée et remplace toutes les valeurs par 0, ce qui
 * équivaut à effacer la ligne.
 *
 * @param row L'indice de la ligne à effacer.
 */
void Board::clearLine(int row) {
    fill(board[row].begin(), board[row].end(), 0);
    //MODIFICATION FAITE
}

/**
 * @brief Déplace une ligne vers le bas dans la grille du plateau de jeu.
 *
 * Cette méthode déplace une ligne vers le bas dans la grille du plateau de jeu,
 * en copiant les valeurs des cases de la ligne spécifiée vers une ligne située
 * plus bas. La ligne d'origine est ensuite effacée.
 *
 * @param row L'index de la ligne à déplacer vers le bas.
 * @param rowsNum Le nombre de lignes à déplacer vers le bas.
 */
void Board::moveDownLine(int row, int rowsNum) {
    //MODIFICATION FAITE
    int destRow = row + rowsNum;
    // Copier les valeurs de la ligne source à la ligne de destination
    copy_backward(board[row].begin(), board[row].end(), board[destRow].end());
    // Effacer la ligne source
    fill(board[row].begin(), board[row].end(), 0);
}

/**
 * @brief Méthode pour vérifier si les positions de la brique actuelle sont vides sur le plateau de jeu.
 *
 * Cette méthode vérifie si toutes les positions occupées par la brique actuelle sont vides
 * dans le plateau de jeu.
 *
 * @return Vrai si toutes les positions de la brique actuelle sont vides, sinon faux.
 */
bool Board::isPosBrickEmpty() {
    //MODIFICATION FAITE
    brick* CurrentBricks = getCurrentBrick();
    vector<position> tiles = CurrentBricks->getPosition();
    return std::all_of(tiles.begin(), tiles.end(), [&](const position& item) {
        return isCasesEmpty(item);
    });
}

/**
 * @brief Méthode pour obtenir le nombre de lignes du tableau.
 *
 * @return Le nombre de lignes du tableau.
 */
int Board::getRowsNum() const
{

    return rowsNum;
}

/**
 * @brief Méthode pour obtenir le nombre de colonnes du tableau.
 *
 * @return Le nombre de colonnes du tableau.
 */
int Board::getColsNum() const
{

    return colsNum;
}


/**
 * @brief Méthode pour vérifier si la brique actuelle est en dehors du plateau de jeu.
 *
 * @return Vrai si la brique actuelle est en dehors du plateau de jeu, sinon faux.
 */
bool Board::isBrickOut() {
    //MODIFICATION FAITE
    brick* currentBricks = getCurrentBrick();
    vector<position> tiles = currentBricks->getPosition();
    return any_of(tiles.begin(), tiles.end(), [this](const position& item) {
        return isCasesOut(item);
    });
}




/**
 * @brief Méthode pour obtenir les positions actuelles de la brique.
 *
 * @return Un vecteur contenant les positions actuelles de la brique.
 */
vector<position>Board::getCurrentBrickPos() const {

    return currentBrick->getPosition();
}



/**
 * @brief Méthode qui vérifie si la brique est tout en bas du plateau.
 *
 * Cette méthode parcourt les positions de la brique actuelle pour vérifier si l'une des positions
 * se situe tout en bas du plateau ou si une position adjacente à la brique est déjà occupée. Si
 * l'une de ces conditions est remplie, la méthode renvoie vrai, sinon elle renvoie faux.
 *
 * @return true si la brique est tout en bas du plateau, sinon false.
 */

bool Board::isBrickBottom()
{
    //MODIFICATION FAITE
    auto currentBrickPos = getCurrentBrickPos();
    return any_of(currentBrickPos.begin(), currentBrickPos.end(), [this](const auto& pos) {
        int x = pos.getRow();
        int y = pos.getColumn();
        return (x + 1 >= rowsNum) || (board[x + 1][y] == 1 && !isPosistionInsideBrick(x, y));
    });
}


/**
 * @brief Méthode qui vérifie si la position est dans la brique actuelle.
 *
 * Cette méthode parcourt les positions de la brique actuelle pour vérifier si la position
 * spécifiée est l'une d'entre elles. Si c'est le cas, la méthode renvoie vrai, sinon elle
 * renvoie faux.
 *
 * @param row La ligne de la position à vérifier.
 * @param col La colonne de la position à vérifier.
 * @return true si la position est dans la brique actuelle, sinon false.
 */

bool Board::isPosistionInsideBrick(int row, int col)
{
    auto currentBrickPos = getCurrentBrickPos();
    return find_if(currentBrickPos.begin(), currentBrickPos.end(), [row, col](const auto& pos) {
        return pos.getRow() == row && pos.getColumn() == col;
    }) != currentBrickPos.end();
}

void Board::setCurrentBrickToNull() {
//    currentBrick = nullptr;
    currentBrick->active = false;
}
};



















