#include "Game.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainMenu *jeu = new MainMenu();
    jeu->show();

    return a.exec();
}