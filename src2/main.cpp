#include "Game.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    /*
    Game* pGame = new Game();
    //Game* pGame = new Game();
    pGame->show();
    // Avoir la fenetre d'une taille précise
    pGame->setFixedSize(400, 800);
    pGame->run();
     */

    Scoreboard* pScoreboard = new Scoreboard();
    pScoreboard->show();

    return a.exec();
}