#include <QWidget>
#include <QPainter>
#include "Board.h"  // Assurez-vous d'inclure votre classe Board

class GameWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr) : QWidget(parent), board(20, 10) {
        setFixedSize(500, 600);  // Définissez une taille fixe basée sur la taille de votre grille
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        drawGrid(painter);
    }

private:
    model::Board board;

    void drawGrid(QPainter &painter) {
        int cellWidth = width() / board.getColsNum();
        int cellHeight = height() / board.getRowsNum();

        for (int row = 0; row < board.getRowsNum(); ++row) {
            for (int col = 0; col < board.getColsNum(); ++col) {
                QColor color = (board.getBoardValue(row, col) == 1) ? Qt::red : Qt::white;
                painter.fillRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight, color);
                painter.drawRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
            }
        }
    }
};
