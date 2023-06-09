#include <QApplication>
#include "SpaceInvaders.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SpaceInvaders* pGame = new SpaceInvaders(qApp->screens()[0]->size());
    pGame->showFullScreen();
    pGame->run();

    return a.exec();
}