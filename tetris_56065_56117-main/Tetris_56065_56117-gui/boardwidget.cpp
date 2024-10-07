#include <QWidget>
#include <QPainter>
#include "Board.h"  // Assurez-vous d'inclure votre classe de jeu

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    BoardWidget(QWidget *parent = nullptr) : QWidget(parent), board(20, 10) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        board.draw(painter);
    }

private:
    model::Board board;  // Assurez-vous que votre classe de jeu est accessible
};
