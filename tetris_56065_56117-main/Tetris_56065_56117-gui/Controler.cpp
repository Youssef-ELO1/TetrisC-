#include "Controler.h"
#include <conio.h>
#include <iostream>

namespace controler {

using namespace std;
using namespace model;
using namespace view;

/**
 * @file Controler.cpp
 * @brief Implémentation des méthodes de la classe Controler
 */

/**
 * @brief Constructeur de la classe Controler.
 *
 * Initialise le contrôleur avec le plateau de jeu et la vue.
 *
 * @param b Référence vers l'objet Board.
 * @param v Référence vers l'objet View.
 */
Controler::Controler(Game &b, View& view): board(b),view(view),  gameOver(false) {
    view.printBienvenu();
    int modeChoice=0;
    cin>>modeChoice;
    while(modeChoice!=1 && modeChoice!=2){
        cin>>modeChoice;}
    if(modeChoice==2){
        view.printBoardperso();
        int row = 0;
        cin>>row;
        int cols = 0;
        cin>>cols;
        Game newB(row,cols);
        board=newB;
        view.setBoard(newB);//à revoir
    }
}

/**
 * @brief Méthode pour afficher le jeu.
 *
 * Cette méthode utilise l'objet View pour afficher le plateau de jeu, le score et le niveau actuels.
 */
void Controler::draw() {
    view.printBoard();
    //Mettre a jour mon plateau
    //->MainWindow::update();
    view.printBoard();
    view.printScore(getScore());
    board.updateLevel(10);
    view.printLevel(getLevel());
    view.printNbLineCleared(getNbLineCleared());
}

int Controler::getInput() {
    int input;
    view.printInputOptions();

    while (true) {
        cin >> input;

        // Vérifie si l'entrée est un chiffre entre 1 et 5
        if (input >= 1 && input <= 7) {
            break; // Sort de la boucle si l'entrée est valide
        } else {
            view.printInvalidInputMessage();
            cin.clear(); // Efface le drapeau d'erreur
            cin.ignore(10000, '\n'); // Vide le buffer
        }
    }
    view.printInputResult(input);
    return input;
}

/**
 * @brief Méthode pour gérer l'entrée utilisateur.
 *
 * Cette méthode obtient la touche pressée par l'utilisateur à l'aide de l'objet View et
 * effectue l'action correspondante sur le plateau de jeu.
 */
void Controler::handleInput(int keyPressed) {
    if(keyPressed==0){
        int keyPressed = getInput();}
    switch (keyPressed) {
    case 1:
        board.moveBrickRight();
        break;
    case 2:
        board.moveBrickLeft();
        break;
    case 3:
        board.moveBrickDown();
        break;
    case 4:
        board.rotateBrick();
        break;
    case 5:
        board.undoRotateBrick();
        break;
    case 6:
        board.drop();
        break;
    case 7:
        exit(0);
        break;
    }
}

/**
 * @brief Méthode pour mettre à jour le jeu.
 *
 * Cette méthode met à jour le plateau de jeu en faisant descendre la brique actuelle et
 * en vérifiant si le jeu est terminé.
 */
void Controler::updateGame() {
    if(!board.updateGame()){
        GameOver();
    }
}

/**
 * @brief Méthode pour gérer la fin de partie.
 *
 * Cette méthode affiche l'écran de fin de partie à l'aide de l'objet View et termine le programme.
 */
void Controler::GameOver()
{
    view.printGameOver();
    gameOver = true;
}

bool Controler::isGameOver(){
    return gameOver;
}

/**
 * @brief Méthode pour obtenir le score actuel.
 *
 * @return Le score actuel.
 */
int Controler::getScore() const {
    return board.getScore();
}

/**
 * @brief Méthode pour obtenir le niveau actuel.
 *
 * @return Le niveau actuel.
 */
int Controler::getLevel() const {
    return board.getLevel();
}

int Controler::getNbLineCleared() const {
    return board.getNbLineCleared();
}

/**
 * @brief Méthode pour vérifier si le joueur a gagné.
 *
 * Cette méthode vérifie si le score actuel est supérieur à 1500, et si c'est le cas,
 * affiche un message de victoire à l'aide de l'objet View.
 *
 * @return true si le joueur a gagné, sinon false.
 */

bool Controler::winner(){
    int currentScore = getScore();
    if(currentScore >= 100000 ){
        view.printWinner();
        return true;
    }
    return false;
}

/**
 * @brief Lance le jeu Tetris.
 *
 * Cette méthode contrôle le déroulement du jeu Tetris en bouclant jusqu'à ce que le jeu se termine
 * ou que le joueur gagne.
 *
 * Le jeu est affiché à l'écran, puis une boucle est exécutée tant que le jeu n'est pas terminé
 * et que le joueur n'a pas gagné. À chaque itération de la boucle, la méthode HandleInput()
 * est appelée pour gérer l'entrée utilisateur, puis la méthode updateGame() est appelée pour
 * mettre à jour l'état du jeu. Enfin, le jeu mis à jour est à nouveau affiché à l'écran.
 */
void Controler::play() {
    draw();
    while(!gameOver && !winner())
    {
        handleInput();
        updateGame();
        draw();
    }
}
model::Board Controler::getBoard(){
   return board.getBoard();
}

}
