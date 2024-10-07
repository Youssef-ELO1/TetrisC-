#include "view.h"
#include <iostream>

/**
 * @file view.cpp
 * @brief Implémentation des méthodes de la classe view
 */

namespace view {

using namespace std;
using namespace model;

/**
 * @brief Constructeur de la classe View.
 *
 * Initialise la vue avec le plateau de jeu spécifié.
 *
 * @param b Référence vers l'objet Board.
 */
View::View(Game& b): model(b) {}

/**
 * @brief Méthode pour afficher le message de bienvenue.
 */
void View::printBienvenu() {
    cout << "Bienvenue au jeu Tetris en vue console ! " << endl;
    cout << "Projet fait par Arnold et Youssef. " << endl;
    cout << "Si votre score est de 10000 points vous avez gagnez ! " << endl;
    cout << "Si vous voulez un jeu par defaut appuie sur 1 sinon 2 !\n " << endl;
}

// Méthode pour demander le nombre de lignes et de colonnes (>6)
void View::printBoardperso() {
    cout << "Choisissez le nombre de lignes et de colonnes :\n "<< endl;
}

/**
 * @brief Méthode pour afficher le plateau de jeu.
 *
 * @param board Le plateau de jeu à afficher.
 */
void View::printBoard(){

    for(int row = 0; row < this->model.getBoard().getRowsNum(); row++) {
        for(int col = 0; col < this->model.getBoard().getColsNum(); col++) {
            vector<position> currentBrickPos = this->model.getBoard().getCurrentBrick()->getPosition();
            position currentPos = position(row, col);
            bool isBrick = false;
            // Vérification si la position est occupée par la brique actuelle
            for(int i = 0; i < currentBrickPos.size(); i++) {
                if(currentBrickPos[i].getRow() == currentPos.getRow() && currentBrickPos[i].getColumn() == currentPos.getColumn()) {
                    isBrick = true;
                    break;
                }
            }
            // Dessin de la brique actuelle ou du contenu de la case du tableau
            if(isBrick) {
                cout << "C" << " ";
            } else if(this->model.getBoard().getBoardValue(row, col) == 1) {
                cout << "X ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

/**
 * @brief Méthode pour afficher le niveau actuel.
 *
 * @param level Le niveau actuel à afficher.
 */
void View::printLevel(int level){
    cout << "Level :  "<< level << endl;
}

/**
 * @brief Méthode pour afficher le score actuel.
 *
 * @param score Le score actuel à afficher.
 */
void View::printScore(int score){

    cout << "Score: "<< score << endl;
}

void View::printNbLineCleared(int nbLineCleared) {
    cout << "Lines: "<< nbLineCleared << endl << endl;
}

/**
 * @brief Méthode pour afficher l'écran de fin de partie.
 */
void View::printGameOver(){

    cout << "Game Over !!!" << endl;
    cout << "Votre score est de " << model.getScore() << endl;
}

void View::printWinner(){
    cout << "Vous avez gagne !" << endl;
    cout << "Votre score est de " << model.getScore() << endl;
}

/**
 * @brief Méthode pour obtenir l'entrée utilisateur.
 *
 * @return Le numéro correspondant à l'action choisie par l'utilisateur.
 */
/*int View::getInput() {
    int input;

    while (true) {
        cout << "Entrez le numero correspondant a votre action :" << endl;
        cout << "1 : Aller a droite" << endl;
        cout << "2 : Aller a gauche" << endl;
        cout << "3 : Descendre" << endl;
        cout << "4 : Rotation" << endl;
        cout << "5 : UndoRotation" << endl;
        cout << "6 : Drop" << endl;
        cout << "7 : Quitter" << endl;
        cin >> input;

        // Vérifie si l'entrée est un chiffre entre 1 et 5
        if (input >= 1 && input <= 7) {
            break; // Sort de la boucle si l'entrée est valide
        } else {
            cout << "Entree invalide ! Veuillez saisir un chiffre entre 1 et 7." << endl;
            cin.clear(); // Efface le drapeau d'erreur
            cin.ignore(10000, '\n'); // Vide le buffer
        }
    }
    cout << "Touche pressee : " << input << endl;
    return input;
}
*/

void View::printInputOptions() {
    cout << "Entrez le numero correspondant a votre action :" << endl;
    cout << "1 : Aller a droite" << endl;
    cout << "2 : Aller a gauche" << endl;
    cout << "3 : Descendre" << endl;
    cout << "4 : Rotation" << endl;
    cout << "5 : UndoRotation" << endl;
    cout << "6 : Drop" << endl;
    cout << "7 : Quitter" << endl;
}

void View::printInvalidInputMessage() {
    cout << "Entree invalide! Veuillez saisir un chiffre entre 1 et 7." << endl;
}

void View::printInputResult(int input) {
    cout << "Touche pressee : " << input << endl;
}

/**
 * @brief Définit le plateau de jeu associé à la vue.
 *
 * Cette méthode permet de définir le plateau de jeu associé à la vue en utilisant une référence.
 *
 * @param b Référence vers l'objet Board à associer à la vue.
 */
/*void View::setBoard(const Board& b){
    //model=b;
    model.setBoard(b);
}
*/

void View::setBoard(const Game& b){
    model=b;
    //model.setBoard(b);
}

}




