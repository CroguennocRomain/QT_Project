#include "Game.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Scoreboard* pGame = new Scoreboard();
    //Game* pGame = new Game();
    pGame->show();
    // Avoir la fenetre d'une taille précise
    pGame->setFixedSize(400, 800);
    //pGame->run();

    return a.exec();
}