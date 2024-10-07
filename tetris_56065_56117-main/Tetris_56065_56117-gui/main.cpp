#include "mainwindow.h"
#include "dimensiondialog.h"

#include<QDialog>
using namespace std;
using namespace model;

/*int main()
{
    // Créer un objet Board
    //Board board = Board();
    Game game = Game();
    // Créer un objet View avec le plateau de jeu
    View view(game);
    // Créer un objet Controler avec le plateau de jeu et la vue
    Controler controler = Controler(game, view);

    //Lance le jeu
    controler.play();
    // Retourner 0 pour indiquer que le programme s'est exécuté avec succès
    return 0;
}*/

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DimensionDialog dialog;

    int rows = 20;
    int cols = 10;

    if (dialog.exec() == QDialog::Accepted) {
        rows = dialog.getRows();
        cols = dialog.getCols();
    }


    Game game = Game(rows, cols);
    //View view(game);
    //Controler controler = Controler(game,view);
    //controler.play();
    MainWindow mainWindow(game);
    mainWindow.update();
    mainWindow.show();
    return app.exec();
}








