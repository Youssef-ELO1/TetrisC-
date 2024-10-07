#include "MainWindow.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QSpacerItem>
#include <QTimer>
#include <QShortcut>
#include <QApplication>
#include <QMessageBox>

#define MOVE_LEFT 2
#define MOVE_RIGHT 1
#define MOVE_DOWN 3
#define ROTATE_CLOCKWISE 4
#define ROTATE_ANTICLOCKWISE 5
#define MOVE_DROP 6

/**
 * @brief Constructeur de la classe MainWindow.
 *
 * Initialise les composants de l'interface utilisateur, connecte les actions des boutons et démarre le chronomètre.
 * Définit également les connexions pour les raccourcis clavier et les actions associées.
 *
 * @param game L'objet Game qui contient l'état du jeu.
 * @param parent Le widget parent de cette fenêtre.
*/
MainWindow::MainWindow(model::Game game, QWidget *parent) : QMainWindow(parent), game(game) {
    setupUI();
    start();
    connect(timer, &QTimer::timeout, this, &MainWindow::moveDown);
    timer->start();
    timer->setInterval(1000);

    chrono = new QTimer(this);

    connect(chrono, &QTimer::timeout, this, &MainWindow::updateChrono);
    chrono->start(1000);
}
/**
 * @brief Met à jour le chronomètre et l'affichage du temps écoulé.
*/
void MainWindow::updateChrono() {
    TimeSeconds++;
    TimeLabel->setText("Time: " + QString::number(TimeSeconds) + " seconds");
}

/**
 * @brief Configure l'interface utilisateur.
 *
 * Crée les widgets nécessaires, configure les dispositions et les styles, et initialise les composants de l'interface.
*/
void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    const int numRows = game.getBoard().rowsNum;  // Nombre de lignes du tableau cells
    const int numCols = game.getBoard().colsNum;  // Nombre de colonnes du tableau cells

    cells = new QFrame**[numCols];// Pointeur vers un pointeur pour alloués pour un tab à 1d.
    for (int i = 0; i < numCols; ++i) {
        cells[i] = new QFrame*[numRows];// Pointeur des rows.
        for (int j = 0; j < numRows; ++j) {
            cells[i][j] = nullptr;
        }
    }

    QFrame *gameFrame = new QFrame();
    gameFrame->setStyleSheet("background-color: #191970;");
    gameFrame->setFixedSize(25 * numCols, 25 * numRows);
    QGridLayout *gridLayout = new QGridLayout(gameFrame);
    gridLayout->setSpacing(0);


    this->setStyleSheet("background-color: white;");

    // Initialisation des cellules QFrame dans le tableau statique
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QFrame *cell = new QFrame(gameFrame);
            cell->setFixedSize(25, 25);
            cell->setStyleSheet("background-color: black; border: 1px solid white;"); // Chaque cellule est noire avec une bordure blanche
            gridLayout->addWidget(cell, row, col);

            // Sauvegarde du pointeur de la cellule dans le tableau cells
            cells[col][row] = cell;
        }
    }

    gameFrame->setLayout(gridLayout);


    //quitButton = createButton("Quit", controlLayout);
    QPushButton *quitButton = new QPushButton("Quit", this);
    quitButton->setStyleSheet("QPushButton { background-color: #8B0000; color: white; border-radius: 5px; padding: 5px 10px; }"
                              "QPushButton:hover { background-color: #B22222; }"); // Style du bouton Quit
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);

    QVBoxLayout *labelLayout = new QVBoxLayout();
    levelLabel = createLabel("Level: 1", labelLayout);
    scoreLabel = createLabel("Score: 0", labelLayout);
    linesClearedLabel = createLabel("Lines Cleared: 0", labelLayout);
    labelLayout->setAlignment(Qt::AlignTop);


    connectButtons();
    QHBoxLayout *quitButtonLayout = new QHBoxLayout();
    quitButtonLayout->addStretch(1);
    quitButtonLayout->addWidget(quitButton);


    // Add gameFrame and labelLayout to mainLayout
    mainLayout->addLayout(quitButtonLayout); // Add quitButtonLayout to mainLayout

    // Add gameFrame and labelLayout to mainLayout
    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(gameFrame, 0, Qt::AlignTop);
    centerLayout->addLayout(labelLayout, 0);
    centerLayout->setAlignment(Qt::AlignHCenter);

    mainLayout->addLayout(centerLayout); // Add centerLayout to mainLayout

    setCentralWidget(centralWidget);
    setWindowTitle("Tetris");
    setFixedSize(750, 750);

    updateCellColor();

    TimeLabel = new QLabel("Time: 0 seconds", this);
    TimeLabel->setStyleSheet("font-size: 14pt; color: red;"); // Appliquer le style CSS
    labelLayout->addWidget(TimeLabel);
}
/**
 * @brief Met à jour la couleur des cellules dans le jeu.
 *
 * Colore spécifiquement la ligne du milieu du plateau de jeu pour le démarrage.
 */
void MainWindow::updateCellColor() {
    int middleRow = game.getBoard().rowsNum / 2; // Find the middle row
    for (int col = 0; col < game.getBoard().colsNum; ++col) {
        QFrame *cell = cells[col][middleRow];
        cell->setStyleSheet("background-color: red; border: 1px solid white;");
    }
}
/**
 * @brief Crée un bouton et l'ajoute à la disposition spécifiée.
 *
 * @param text Le texte à afficher sur le bouton.
 * @param layout La disposition à laquelle le bouton sera ajouté.
 * @return Un pointeur vers le QPushButton créé.
 */
QPushButton* MainWindow::createButton(const QString &text, QLayout *layout) {
    QPushButton *button = new QPushButton(text);
    layout->addWidget(button);
    return button;
}
/**
 * @brief Crée un QLabel et l'ajoute à la disposition spécifiée.
 *
 * @param text Le texte à afficher sur le label.
 * @param layout La disposition à laquelle le label sera ajouté.
 * @return Un pointeur vers le QLabel créé.
 */
QLabel* MainWindow::createLabel(const QString &text, QLayout *layout) {
    QLabel *label = new QLabel(text);
    label->setStyleSheet("color: black;");
    label->setStyleSheet("font-size: 20pt; color: black;");
    layout->addWidget(label);
    return label;
}

/**
 * @brief Connecte les actions des boutons aux slots appropriés.
 *
 * Associe les raccourcis clavier aux mouvements et rotations des pièces dans le jeu.
 */
void MainWindow::connectButtons() {
    QShortcut *leftShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    QShortcut *rightShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);
    QShortcut *downShortcut = new QShortcut(QKeySequence(Qt::Key_Down), this);
    QShortcut *cwShortcut = new QShortcut(QKeySequence(Qt::Key_Up), this);
    QShortcut *acwShortcut = new QShortcut(QKeySequence(Qt::Key_R), this);
    QShortcut *dropShortcut = new QShortcut(QKeySequence(Qt::Key_D), this);

    connect(leftShortcut, &QShortcut::activated, this, &MainWindow::moveLeft);
    connect(rightShortcut, &QShortcut::activated, this, &MainWindow::moveRight);
    connect(downShortcut, &QShortcut::activated, this, &MainWindow::moveDown);
    connect(cwShortcut, &QShortcut::activated, this, &MainWindow::rotateClockwise);
    connect(acwShortcut, &QShortcut::activated, this, &MainWindow::rotateAntiClockwise);
    connect(dropShortcut, &QShortcut::activated, this, &MainWindow::moveDrop);
}
/**
 * @brief Déplace la pièce de jeu vers la gauche.
 */
void MainWindow::moveLeft() {
    game.moveBrickLeft();
    update();
}
/**
 * @brief Déplace la pièce de jeu vers la droite.
 */
void MainWindow::moveRight() {
    game.moveBrickRight();// Assumed MOVE_RIGHT is defined somewhere
    update();
}
/**
 * @brief Déplace la pièce de jeu vers le bas.
 */
void MainWindow::moveDown() {
    game.moveBrickDown(); // Assumed MOVE_DOWN is defined somewhere
    update();
}
/**
 * @brief Effectue une rotation horaire de la pièce de jeu.
 */
void MainWindow::rotateClockwise() {
    game.rotateBrick(); // Assumed ROTATE_CLOCKWISE is defined somewhere
    update();
}
/**
 * @brief Effectue une rotation antihoraire de la pièce de jeu.
 */
void MainWindow::rotateAntiClockwise() {
    game.undoRotateBrick(); // Assumed ROTATE_ANTICLOCKWISE is defined somewhere
    update();
}

/**
 * @brief Fait chuter la pièce de jeu instantanément en bas du plateau.
 */
void MainWindow::moveDrop() {
    game.drop(); // Assumed MOVE_DROP is defined somewhere
    update();
}
/**
 * @brief Met à jour l'état du jeu, incluant le niveau, le score, et les lignes nettoyées.
 *
 * Vérifie également les conditions de fin de jeu, et affiche les messages appropriés en cas de victoire ou de défaite.
 */
void MainWindow::update(){
    game.updateLevel(10);
    timer->setInterval(game.getLevelInterval()); // renvoie l'unité de temps au niveau actuelle

    levelLabel->setText("Level: " + QString::number(game.getLevel()));
    scoreLabel->setText("Score: " + QString::number(game.getScore()));
    linesClearedLabel->setText("Lines Cleared: " + QString::number(game.getNbLineCleared()));

    if (!game.updateGame()) {
        timer->stop();
        close();
        QMessageBox gameOverBox;
        gameOverBox.setWindowTitle("Game Over");
        gameOverBox.setText("<h2 style=\"font-size: 20pt;\">Score: " + QString::number(game.getScore()) +"</h2>");
        gameOverBox.setStandardButtons(QMessageBox::Ok);
        gameOverBox.setDefaultButton(QMessageBox::Ok);
        gameOverBox.exec();
    }

    // Contions de victoire (doivent être toutes réunies)
    if (game.getScore() > 10000 || TimeSeconds > 300 || game.getNbLineCleared() == 20) {
        timer->stop();
        close();
        QMessageBox winBox;
        winBox.setWindowTitle("You Won!");
        winBox.setText("<h2 style=\"font-size: 20pt;\">Score: " + QString::number(game.getScore()) +"</h2>");
        winBox.setStandardButtons(QMessageBox::Ok);
        winBox.setDefaultButton(QMessageBox::Ok);
        winBox.exec();
    }


    game.updateGame();
    for (int row = 0; row < game.getBoard().getRowsNum(); row++) {
        for (int col = 0; col < game.getBoard().getColsNum(); col++) {
            std::vector<model::position> currentBrickPos = game.getBoard().getCurrentBrick()->getPosition();
            model::position currentPos = model::position(row, col);
            bool isBrick = false;
            // Vérification si la position est occupée par la brique actuelle
            for (int i = 0; i < currentBrickPos.size(); i++) {
                if (currentBrickPos[i].getRow() == currentPos.getRow() && currentBrickPos[i].getColumn() == currentPos.getColumn()) {
                    isBrick = true;
                    break;
                }
            }
            // Dessin de la brique actuelle ou du contenu de la case du tableau
            if (isBrick){
                cells[col][row]->setStyleSheet("background-color: #800000; border: 1px solid white;");
            }else if (game.getBoard().getBoardValue(row, col) == 1) {
                cells[col][row]->setStyleSheet("background-color: #228B22; border: 1px solid white;");
            }else {
                cells[col][row]->setStyleSheet("background-color: black; border: 1px solid white;");
            }
        }
    }
}

/**
 * @brief Lance le jeu.
 */
void MainWindow::start(){
    update();
}















