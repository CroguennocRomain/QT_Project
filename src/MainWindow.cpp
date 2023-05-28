#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Invasion des aliens");
    this->resize(400, 800);

    /* Menu d'informations */
    helpMenu = menuBar()->addMenu(tr("&Informations"));

    QAction* actionHelp = new QAction(tr("&A propos"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    QAction* actionCommande = new QAction(tr("&Commandes"), this);
    connect(actionCommande, SIGNAL(triggered()), this, SLOT(slot_commandeMenu()));
    QAction* actionRegles = new QAction(tr("&Regles"), this);
    connect(actionRegles, SIGNAL(triggered()), this, SLOT(slot_reglesMenu()));
    QAction* actionQuit = new QAction(tr("&Quitter"), this);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    helpMenu->addAction(actionHelp);
    helpMenu->addAction(actionCommande);
    helpMenu->addAction(actionRegles);
    helpMenu->addAction(actionQuit);

}

MainWindow::~MainWindow(){
    delete this->mainScene;
    delete this->mainView;
    delete this->helpMenu;
}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("A propos");
    msgBox.setText("Un petit projet de C++/Qt créé par PAITIER Mathias et CROGUENNOC Romain.");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_commandeMenu() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Commandes");
    msgBox.setInformativeText("Z : avancer vers le haut\n"
                              "Q : avancer vers la gauche\n"
                              "S : avancer vers le bas\n"
                              "D : avancer vers la droite\n\n"

                              "P : mettre / enlever le jeu en pause\n");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_reglesMenu() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Regles");
    msgBox.setInformativeText("Le but du jeu est de tuer les aliens qui envahissent l'espace !\n"
                              "Pour cela, il faut les toucher avec des missiles.\n"
                              "Trois coups sur le vaisseau et il est détruit !\n"
                              "ATTENTION AUX ASTEROIDES !!\n\n"
                              "Bonne chance !\n");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}