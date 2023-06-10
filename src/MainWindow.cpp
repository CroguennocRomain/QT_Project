#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Invasion des aliens");
    this->resize(SCREEN_WIDTH+50, SCREEN_HEIGHT+50);

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
    msgBox.setInformativeText("Q : Avancer vers la gauche\n"
                              "S : Avancer vers le bas\n"

                              "ESPACE : Tirer un missile\n");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_reglesMenu() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Regles");
    msgBox.setInformativeText("Le but du jeu est de tuer les aliens qui envahissent l'espace !\n"
                              "Pour cela, il faut les toucher avec vos missiles.\n"
                              "Si votre vaisseau est touché une fois ou si la Terre que vous venez de quitter est attaquée trois fois c'est la fin de l'aventure !\n"
                              "ATTENTION AUX ASTEROIDES !!\n\n"
                              "N'oubliez pas d'entrer votre nom dans le champ de texte à côter du bouton 'Jouer'.\n"
                              "Bonne chance soldat !!\n");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}