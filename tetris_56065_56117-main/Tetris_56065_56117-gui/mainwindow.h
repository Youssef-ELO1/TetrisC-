#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include "game.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(model::Game game,QWidget *parent=nullptr);
    void update();
    void start();

private:
    void setupUI();

    void updateCellColor();

    QFrame*** cells;// Ici c'est un pointeur vers un pointeur vers un pointeur pour alloué un tableau a 2d.
    QPushButton *exitButton;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *Rigth;
    QLabel *scoreLabel;
    QLabel *levelLabel;
    QLabel *nextShapeLabel;
    QLabel *TimeLabel;
    QLabel* linesClearedLabel;
    QFrame *nextShapeFrame;
    model::Game game;

    QPushButton* createButton(const QString &text, QLayout *layout);
    QLabel* createLabel(const QString &text, QLayout *layout);
    QTimer *timer = new QTimer();
    QTimer *chrono;
    int TimeSeconds = 0;

private slots:

    void connectButtons();
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotateClockwise();
    void rotateAntiClockwise();
    void moveDrop();
    void updateChrono();
};

#endif // MAINWINDOW_H
