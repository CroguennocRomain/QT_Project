#include "Game.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe ButtonPanel #------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
ButtonPanel::ButtonPanel(QWidget *parent) : QWidget(parent) {
    /* <>---< Création des bouttons >---<> */
    startButton = new QPushButton("Jouer", this);
    quitButton = new QPushButton("Quitter", this);
    textInput = new QLineEdit(this);

    /* <>---< Création du layout >---<> */
    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->addWidget(textInput);
    layout->addWidget(startButton);
    layout->addWidget(quitButton);

    setLayout(layout);

    /* <>---< Connexion des bouttons >---<> */
    connect(startButton, &QPushButton::clicked, this, [=]() {
        // Récupérer le texte saisi
        playerName = textInput->text();

    });
    QObject::connect(startButton, SIGNAL(clicked()), parent, SLOT(startGame()));
    QObject::connect(quitButton, SIGNAL(clicked()), parent, SLOT(close()));
}

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
ButtonPanel::~ButtonPanel() {
    delete startButton;
    delete quitButton;
}

/* <-__---__---__---__---__--- Getters ---__---__---__---__--- -> */
QString ButtonPanel::getPlayerName() const {
    return playerName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Structure Data #----------------------------------------#
   #-------------------------------------------------------------# */
// Permet de faciliter la comparaison des scores pour l'afficher dans le scoreboard
struct Data {
    QString name;
    int score;
};

bool compareScores(const Data& data1, const Data& data2) {
    return data1.score > data2.score;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Scoreboard #-------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Scoreboard::Scoreboard(QWidget* parent) : QTableWidget(parent) {
    /* <>---< Paramétrage du tableau >---<> */
    this->setFixedSize(380,320);
    this->setRowCount(5);    // On veut afficher les 5 meilleurs scores
    this->setColumnCount(2); // Deux colonnes pour le nom et le score
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QStringList headerLabels;
    headerLabels << "Nom" << "Score"; // En-têtes des colonnes
    this->setHorizontalHeaderLabels(headerLabels);

    /* <>---< Remplissage du tableau >---<> */
    QVector<Data> dataVec;
    // Lire le fichier CSV et stocker les données dans le vecteur de Data
    QFile file("../data/score.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 2) {
                Data data;
                data.name = fields[0].trimmed();
                data.score = fields[1].trimmed().toInt();
                dataVec.append(data);
            }
        }
        file.close();
    } else {
        qDebug() << "Erreur lors de l'ouverture du fichier.";
    }

    std::sort(dataVec.begin(), dataVec.end(), compareScores);

    for (int row = 0; row < qMin(5, dataVec.size()); ++row) {
        Data data = dataVec[row];
        QTableWidgetItem* nameItem = new QTableWidgetItem(data.name);
        QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(data.score));
        this->setItem(row, 0, nameItem); // Colonne du nom
        this->setItem(row, 1, scoreItem); // Colonne du score
    }

    // Définir la taille des colonnes pour qu'elles prennent toute la largeur du tableau
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe MainMenu #---------------------------------------#
   #-------------------------------------------------------------# */

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
    /* <>---< Création des paramètres de la fenêtre >---<> */
    this->setWindowTitle("Invasion des aliens - Menu principal");
    setCursor(Qt::PointingHandCursor);
    setFixedSize(400, 400);

    /* <>---< Création du menu bar >---<> */
    QMenuBar* menuBar = new QMenuBar(this);

    QMenu* menu = menuBar->addMenu(tr("&Informations"));
    // Création des actions du menu
    QAction* actionHelp = new QAction(tr("&A propos"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    QAction* actionCommande = new QAction(tr("&Commandes"), this);
    connect(actionCommande, SIGNAL(triggered()), this, SLOT(slot_commandeMenu()));
    QAction* actionRegles = new QAction(tr("&Regles"), this);
    connect(actionRegles, SIGNAL(triggered()), this, SLOT(slot_reglesMenu()));
    // Ajout des actions au menu
    menu->addAction(actionHelp);
    menu->addAction(actionCommande);
    menu->addAction(actionRegles);
    /* <>---< Création du layout >---<> */
    QVBoxLayout* layout = new QVBoxLayout();
    // Ajout du menu bar
    layout->setMenuBar(menuBar);
    // Création du tableau des scores
    this->scoreboard = new Scoreboard(this);
    layout->addWidget(scoreboard);
    // Ajout des boutons
    this->buttonPanel = new ButtonPanel(this);
    layout->addWidget(buttonPanel);

    setLayout(layout);
}

void MainMenu::startGame() {
    // Lorsque le bouton "Jouer" est cliqué, ouvre la fenêtre du jeu
    Game* game = new Game(this->buttonPanel->getPlayerName());
    game->show();
    game->setFixedSize(400, 800);
    game->run();

    // Ferme le menu principal
    this->close();
}

/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
/* <>---< Slots du menu "A propos" >---<> */
void MainMenu::slot_aboutMenu(){
    QMessageBox msgBox;
    // Titre de la fenetre
    msgBox.setWindowTitle("A propos");
    // Texte de la fenetre
    msgBox.setText("Un petit projet de C++/Qt créé par PAITIER Mathias et CROGUENNOC Romain.");
    // On souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.setModal(true);
    msgBox.exec();
}

/* <>---< Slots du menu "Commandes" >---<> */
void MainMenu::slot_commandeMenu() {
    QMessageBox msgBox;
    // Titre de la fenetre
    msgBox.setWindowTitle("Commandes");
    // Texte de la fenetre
    msgBox.setInformativeText("Q : Avancer vers la gauche\n"
                              "S : Avancer vers le bas\n\n"
                              "ESPACE : Tirer un missile\n");
    // On souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.setModal(true);
    msgBox.exec();
}

/* <>---< Slots du menu "Regles" >---<> */
void MainMenu::slot_reglesMenu() {
    QMessageBox msgBox;
    // Titre de la fenetre
    msgBox.setWindowTitle("Regles");
    // Texte de la fenetre
    msgBox.setInformativeText("Le but du jeu est de tuer les aliens qui envahissent l'espace !\n\n"
                              "Pour cela, il faut les toucher avec vos missiles.\n"
                              "Si votre vaisseau est touché une fois ou si la Terre que vous venez de quitter est attaquée trois fois c'est la fin de l'aventure !\n"
                              "ATTENTION AUX ASTEROIDES !!\n\n"
                              "N'oubliez pas d'entrer votre nom dans le champ de texte à côter du bouton 'Jouer'.\n"
                              "Bonne chance soldat !!\n");

    msgBox.setModal(true);
    msgBox.exec();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Game #-------------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Game::Game(QString playerName, QWidget* parent) : QGraphicsView(parent) {
    this->playerName = playerName;

    this->setWindowTitle("Invasion des aliens");
    // Pour que chaque partie soit aléatoire
    std::srand(time(0));
    /* <>---< Création de la scene >---<> */
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);
    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    /* <>---< Création de l'image de fond >---<> */
    this->background.load("../img/BackGround.jpg");
    this->setSceneRect(0,0, background.width(), background.height());

    /* <>---< Création du style de la fenêtre >---<> */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");

    /* <>---< Création du timer pour l'animation >---<> */
    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(30);

}

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
Game::~Game() {
    delete this->timer;
    delete this->spawnTimer;
    delete this->myPlayer;
    delete this->playerPoints;
}

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
/* <>---< Création de l'image de fond >---<> */
void Game::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

/* <>---< Début du jeu >---<> */
void Game::run() {
    // On efface la scene et on cache le curseur
    scene()->clear();
    setCursor(Qt::BlankCursor);

    /* <>---< Création du joueur >---<> */
    // On initialise de manière aléatoire la position du joueur
    int posInit;
    do {
        posInit = (rand() % 3200);
    } while (posInit < 700 - (EntitySize.height()/2)  || posInit > 3100 - EntitySize.width()); // On veut que le joueur soit dans l'écran                 // On ajoute 800 pour ne pas au bout du scrolling (pour éviter d'être TP dès le début)
    // Création du joueur
    myPlayer = new Player();
    myPlayer->setPos( (SCREEN_WIDTH - EntitySize.width()) / 2 , posInit - (EntitySize.height()/2) );
    // Permet de gérer les évènements clavier
    myPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    myPlayer->setFocus();

    scene()->addItem(myPlayer);
    // On connecte le joueur à l'ajout de points à son score
    connect(myPlayer, &Player::sigIncreaseScore, this, &Game::onIncreaseScore);

    /* <>---< Création des infos du joueur >---<> */
    playerPoints = new Points();
    scene()->addItem(playerPoints);

    /* <>---< Création des aliens tous les "spawnSpacing" millisecondes >---<> */
    this->spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout, this, &Game::onCreateEnemy);
    spawnTimer->start(spawnSpacing);
}

/* <>---< Gestion des évènements clavier >---<> */
void Game::isOver(){
    // Si le joueur n'a plus de PVs c'est la fin
    if(playerPoints->getHealth() <= 0){
        playerPoints->reset();
        onGameOver();
    }
}

/* <>---< Ajout de données dans le CSV >---<> */
void Game::addDataToCSV(QString playerName, int score) {
// On ouvre le fichier CSV
    QFile file("../data/score.csv");
    // On vérifie que le fichier est bien ouvert
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    // On écrit les données dans le fichier
    QTextStream out(&file);
    out << playerName << "," << score << "\n";
    file.close();
}

/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
/* <>---< Gestion de la création des ennemis >---<> */
void Game::onCreateEnemy(){
    if(!this->over) {
        // On initialise de manière aléatoire la position latérale de l'alien
        int nPos;
        do {
            nPos = (rand() % SCREEN_WIDTH);
        } while (nPos < EntitySize.width() || nPos > SCREEN_WIDTH - EntitySize.width()); // On veut que l'alien soit dans l'écran

        // On veut que l'alien soit de couleur aléatoire
        int nColor = rand() % 5;
        // Création de l'alien, sa position est en dehors de l'écran (au dessus)
        Alien* pAlien = new Alien(static_cast<Color>(nColor));
        pAlien->setPos(nPos, this->myPlayer->y() - 700);
        // On ajoute l'alien à la scene
        scene()->addItem(pAlien);
        // On connecte l'alien aux conditions de défaite
        connect(pAlien, &Alien::sigDecreaseHealth, this, &Game::onDecreaseHealth);
        connect(pAlien, &Alien::sigGameOver, this, &Game::onGameOver);
    }

}

/* <>---< Gestion de l'augmentation du score >---<> */
void Game::onIncreaseScore(){
    // TODO : Récupérer le score de l'alien pour l'ajouter au score du joueur
    playerPoints->increaseScore(50);
}

/* <>---< Gestion de la diminution des PVs >---<> */
void Game::onDecreaseHealth(){
    playerPoints->decreaseHealth();
}

/* <>---< Gestion de la fin du jeu >---<> */
void Game::onGameOver(){
    // Ecriture du score dans le fichier
    addDataToCSV(playerName, playerPoints->getScore());

    // On fait comme dans un destructeur sinon d'autres fenetres se créent en boucle
    this->over = true;
    delete this->timer;
    delete this->spawnTimer;
    delete this->myPlayer;
    delete this->playerPoints;
    close();

    MainMenu* mainMenu = new MainMenu();
    mainMenu->show();
}

/* <>---< Gestion des animations >---<> */
void Game::update() {
    /* <>---< Gestion de la fin du jeu >---<> */
    isOver();

    /* <>---< On place la vue sur le joueur >---<> */
    // Le joueur est excentré de 300 pixels vers le bas pour que le joueur puisse voir les aliens arriver
    if (myPlayer != nullptr) {
        QPointF target(myPlayer->x() + EntitySize.width() / 2, myPlayer->y() + EntitySize.height() / 2 - 300);
        centerOn(target);
    }

    /* <>---< Suppression de l'alien si il sort de l'écran et diminution des PVs >---<> */
    for (auto& item : scene()->items()) {
        if (item->type() == Alien::Type) {
            if (item->y() > myPlayer->y() + 100) {
                scene()->removeItem(item);
                emit static_cast<Alien*>(item)->sigDecreaseHealth();
                delete item;
            }
        }
    }

    /* <>---< Gestion des déplacements >---<> */
    // Déplacement à gauche
    if (this->isMovingLeft) {
        if (myPlayer->x() > 0) {
            myPlayer->setPos(myPlayer->x() - PlayerSpeed, myPlayer->y());
        }
    } // Déplacement à droite
    else if (this->isMovingRight) {
        if (myPlayer->x() + EntitySize.width() < SCREEN_WIDTH) {
            myPlayer->setPos(myPlayer->x() + PlayerSpeed, myPlayer->y());
        }
    }

    /* <>---< Gestion du scrolling >---<> */
    // On déplace le joueur et ses infos vers le haut
    myPlayer->setPos(myPlayer->x(), myPlayer->y() - m_Scrolling);
    playerPoints->setPos(0, myPlayer->y()-675);
    // Si on est tout en haut, on se téléporte en bas (les valeurs sont mises de telle sorte que le joueur ne voit pas le déplacement instantané)
    if(myPlayer->y() <= 700-m_Scrolling-(EntitySize.height()/2) ) {  // Limite haute
        // Déplacer le joueur
        myPlayer->setPos(myPlayer->x(), myPlayer->y()+2400);
        // Déplacer tous les aliens
        for (auto& item : scene()->items()) {
            if (item->type() == Alien::Type) {
                item->setPos(item->x(), item->y() + 2400);
            }
            else {
                break;
            }
        }
    }

    /* <>---< Gestion du spawn des aliens >---<> */
    // Plus le score augmente, plus les aliens arrivent souvent
    // pour chaques valeurs du QVector, on augmente le spawnSpacing
    for (int i = 0; i < spaceSwpan.size(); i++) {
        if (!spaceSwpan[i] && playerPoints->getScore() >= (i+1)*1500) {
            spaceSwpan[i] = true;
            spawnSpacing -= 100;
            break;
        }
    }


}

/* <-__---__---__---__---__--- Events ---__---__---__---__--- -> */
/* <>---< Gestion des évènements clavier >---<> */
void Game::keyPressEvent(QKeyEvent* event) {

    // Si le jeu n'est pas en pause on peut donc jouer
    if (this->timer->isActive()) {

        // Déplacement à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = true;
        }

        // Déplacement à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = true;
        }

        // Tirer
        if (event->key() == Qt::Key_Space) {
            myPlayer->shoot();
        }

    }
}

void Game::keyReleaseEvent(QKeyEvent *event) {
    // Si le jeu n'est pas en pause on peut donc jouer
    if (this->timer->isActive()) {

        // Bouger à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = false;
        }

        // Bouger à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = false;
        }

    }
}