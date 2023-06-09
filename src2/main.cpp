#include <QApplication>
#include "SpaceInvaders.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SpaceInvaders* pGame = new SpaceInvaders();
    pGame->show();
    // Avoir la fenetre d'une taille précise
    pGame->setFixedSize(410, 810);
    pGame->run();

    return a.exec();
}