#include "game.h"


namespace model {

using namespace std;

Game::Game() : board(), score(0), level(1), nbLineCleared(0), lineClearedForLevel(0)
{
    //board.initialise(); //Peut-être à effacer
}

Game::Game(int row,int col) : board(row, col), score(0), level(1), nbLineCleared(0),
    lineClearedForLevel(0)
{
    //board.initialise(); //Peut-être à effacer
}


/**
 * @brief Méthode pour effacer toutes les lignes complètes du tableau.
 *
 * Parcourt le tableau de bas en haut, vérifie si chaque ligne est pleine,
 * et efface les lignes complètes en déplaçant les lignes situées au-dessus vers le bas.
 * Invrémente le nombre de ligne effacé.
 *
 * @return Le nombre de lignes effacées.
 */
int Game::clearAllLines() {
    int currentCompleted = 0;
    for(int row = board.getRowsNum() - 1; row >= 0; row--){
        if(board.rowFull(row)) {
            board.clearLine(row);
            currentCompleted++;
            nbLineCleared++;
            lineClearedForLevel++;
        } else if (currentCompleted > 0) {
            board.moveDownLine(row, currentCompleted);
        }
    }
    return currentCompleted;
}

/**
 * @brief Méthode pour déplacer la brique actuelle vers la gauche.
 *
 * Cette méthode déplace la brique actuelle vers la gauche d'une colonne. Si la brique sort
 * du tableau ou entre en collision avec une autre brique, elle est ramenée à sa position
 * précédente. Si elle se trouve tout en bas du plateau, la brique actuelle est verrouillée.
 */
void Game::moveBrickLeft() {
    brick* CurrentBricks = board.getCurrentBrick();

    CurrentBricks->move(0, -1);
    if(board.isBrickOut()|| !board.isPosBrickEmpty()){
        CurrentBricks->move(0,1);
    }
    else if(board.isBrickBottom())
    {

        board.setLockedBrick();
        board.setCurrentBrickToNull();
    }

}

/**
 * @brief Méthode pour déplacer la brique actuelle vers la droite.
 *
 * Cette méthode déplace la brique actuelle vers la droite d'une colonne. Si la brique sort
 * du tableau ou entre en collision avec une autre brique, elle est ramenée à sa position
 * précédente. Si elle se trouve tout en bas du plateau, la brique actuelle est verrouillée.
 */
void Game::moveBrickRight() {
    brick* CurrentBricks = board.getCurrentBrick();

    CurrentBricks->move(0, 1);
    if(board.isBrickOut() || !board.isPosBrickEmpty()){
        CurrentBricks->move(0,-1);
    }
    else if (board.isBrickBottom()) {
        board.setLockedBrick();
        board.setCurrentBrickToNull();
    }

}


/**
 * @brief Méthode pour descendre la brique d'une ligne.
 *
 * Cette méthode déplace la brique actuelle vers le bas d'une ligne. Si la brique sort du tableau
 * ou entre en collision avec une autre brique, elle est verrouillée dans sa position actuelle.
 * Elle met également à jour le score avec le nombre de lignes complètes effacées.
 */
void Game::moveBrickDown() {
    brick* CurrentBricks = board.getCurrentBrick();
    CurrentBricks->move(1, 0);
    updateScore(clearAllLines(), 1);
    if(board.isBrickOut() || !board.isPosBrickEmpty()) {

        CurrentBricks->move(-1,0);
        board.setLockedBrick();
        board.setCurrentBrickToNull();
    }
}

/**
 * @brief Méthode pour faire tourner la brique actuelle dans le sens horloger.
 *
 * Cette méthode fait tourner la brique actuelle. Si la rotation amène la brique en dehors
 * du tableau ou en collision avec une autre brique, elle est verrouillée dans sa position actuelle.
 */
void Game::rotateBrick() {
    brick* CurrentBricks = board.getCurrentBrick();
    CurrentBricks->rotate();
    if(board.isBrickOut() ||  !board.isPosBrickEmpty()){
        CurrentBricks->undoRotate();
    }
    else if(board.isBrickBottom()) {
        board.setLockedBrick();
        board.setCurrentBrickToNull();
    }
}

/**
 * @brief Méthode pour faire tourner la brique actuelle dans le sens anti horloger
 *
 * Cette méthode fait tourner la brique actuelle. Si la rotation amène la brique en dehors
 * du tableau ou en collision avec une autre brique, elle est verrouollée dans sa position actuelle.
 */
void Game::undoRotateBrick() {
    brick* CurrentBricks = board.getCurrentBrick();
    CurrentBricks->undoRotate();
    if(board.isBrickOut() ||  !board.isPosBrickEmpty()){
        CurrentBricks->rotate();
    }
    else if(board.isBrickBottom()) {
        board.setLockedBrick();
        board.setCurrentBrickToNull();
    }
}

/**
 * @brief Fait tomber la brique actuelle jusqu'à ce qu'elle rencontre une autre brique ou atteigne le bas du plateau de jeu.
 *
 * Cette méthode déplace la brique actuelle vers le bas jusqu'à ce qu'elle soit bloquée par une autre brique
 * ou atteigne le bas du plateau de jeu. Elle retourne la hauteur de chute de la brique.
 *
 * @return La hauteur de chute de la brique.
 */
int Game::drop() {
    brick* CurrentBricks = board.getCurrentBrick();
    int dropHeight = 0;

    while(!board.isBrickOut() && board.isPosBrickEmpty()) {
        CurrentBricks->move(1, 0);
        dropHeight++;
    }

    CurrentBricks->move(-1, 0);
    board.setLockedBrick();
    board.setCurrentBrickToNull();

    updateScore(clearAllLines(), dropHeight);

    return dropHeight;
}

/**
 * @brief Méthode pour mettre à jour le score.
 *
 * La méthode calcule les points gagnés en fonction du nombre de lignes effacées et de la distance
 * parcourue par la brique vers le bas. Elle met également à jour le niveau si le nombre de lignes
 * effacées est un multiple de 2.
 *
 * @param LinesCleared Le nombre de lignes effacées.
 * @param dropHeight Le nombre de cases traversées lors du drop.
 */
void Game::updateScore(int LinesCleared, int dropHeight)
{
    int points = 0;
    //MODIFICATION FAITE
    switch (LinesCleared) {
    case 0:
        points = (40 * LinesCleared + dropHeight) * level;
        break;
    case 1:
        points = (40 * LinesCleared + dropHeight) * level;
        break;
    case 2:
        points = (100 * LinesCleared + dropHeight) * level;
        break;
    case 3:
        points = (300 * LinesCleared + dropHeight) * level;
        break;
    case 4:
        points = (1200 * LinesCleared + dropHeight) * level;
        break;
    default:
        break;
    }

    score += points;

}

/**
 * @brief Met à jour le niveau du jeu.
 *
 * Cette méthode incrémente le niveau du jeu toutes les 10 lignes effacées.
 * Le niveau maximal est spécifié par le paramètre maxLevel. Pour éviter que
 * le niveau continue de monter lorsque le nombre de ligne effacé est un multiple
 * de 10 et qu'on ne soit pas encore à 11, on remet lineClearedForLevel à 0.
 *
 * @param maxLevel Le niveau maximal autorisé dans le jeu.
 */
void Game::updateLevel(int maxLevel) {
    if((lineClearedForLevel >= 10) && (level < maxLevel)) {
        level += lineClearedForLevel / 10;
        lineClearedForLevel = lineClearedForLevel % 10;
    }
}

/**
 * @brief Retourne l'unité de temps (en ms) en fonction du niveau.
 */
int Game::getLevelInterval() {
    switch (level) {
    case 1:
        return ((60.0 / 60.0) * 1000);
    case 2:
        return ((53.0 / 60.0) * 1000);
    case 3:
        return ((49.0 / 60.0) * 1000);
    case 4:
        return ((45.0 / 60.0) * 1000);
    case 5:
        return ((41.0 / 60.0) * 1000);
    case 6:
        return ((37.0 / 60.0) * 1000);
    case 7:
        return ((33.0 / 60.0) * 1000);
    case 8:
        return ((28.0 / 60.0) * 1000);
    case 9:
        return ((23.0 / 60.0) * 1000);
    case 10:
        return ((18.0 / 60.0) * 1000);
    case 11:
        return ((13.0 / 60.0) * 1000);
    case 12:
        return ((11.0 / 60.0) * 1000);
    case 13:
        return ((9.0 / 60.0) * 1000);
    case 14:
        return ((8.0 / 60.0) * 1000);
    case 15:
        return ((7.0 / 60.0) * 1000);
    case 16:
        return ((6.0 / 60.0) * 1000);
    case 17:
        return ((5.0 / 60.0) * 1000);
    case 18:
        return ((4.0 / 60.0) * 1000);
    case 19:
        return ((3.0 / 60.0) * 1000);
    default:
        return ((2.0 / 60.0) * 1000);
    }
}


/**
 * @brief Méthode pour obtenir le score actuel.
 *
 * @return Le score actuel.
 */
int Game::getScore() const {
    return score;
}

/**
 * @brief Méthode pour obtenir le niveau actuel.
 *
 * @return Le niveau actuel.
 */
int Game::getLevel() const
{
    return level;
}

/**
 * @brief Méthode pour obtenir le nombre de lignes effacées.
 *
 * @return Le nombre de ligne effacées pendant la partie.
 */
int Game::getNbLineCleared() const {
    return nbLineCleared;
}

Board Game::getBoard() {
    return this->board;
}


/**
 * @brief Méthode pour mettre à jour le plateau de jeu.
 *
 * Si la brique actuelle est nulle, elle génère une nouvelle brique et vérifie si elle peut être placée
 * sur le plateau. Si elle ne peut pas, la méthode retourne faux. Sinon, elle retourne vrai.
 *
 * @return Vrai si la mise à jour du tableau a réussi, sinon faux.
 */
bool Game::updateGame(){
    if (board.getCurrentBrick()->active) {
        return true;
    }

    board.setNewRandomCurrentBrick();
    return board.isPosBrickEmpty();
}

}
