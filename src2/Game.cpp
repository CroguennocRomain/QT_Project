#include "Game.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Scoreboard #-------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Scoreboard::Scoreboard(QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);
    //donner un nom à la page
    setWindowTitle("Tableau de scores");
    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //this->background.load("../img/space-invader.jpg");
    //this->setSceneRect(0,0, background.width(), background.height());

    QWidget* centralWidget = new QWidget(this);
    //setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(5);
    tableWidget->setColumnCount(1);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(tableWidget);
    bestScoreLabel = new QLabel(this);
    bestScoreLabel->setText("Meilleur score : 0");
    bestScoreLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(bestScoreLabel);


    QStringList headerLabels;
    headerLabels << "Score";
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    QList<int> scores;
    scores << 100 << 200 << 150 << 120 << 180;

    int bestScore = 0;

    for (int row = 0; row < scores.size(); ++row) {
        int score = scores[row];
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(score));
        tableWidget->setItem(row, 0, item);

        if (score > bestScore) {
            bestScore = score;
        }
    }

    bestScoreLabel->setText("Meilleur score : " + QString::number(bestScore));

    tableWidget->resizeColumnsToContents();
}

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
Scoreboard::~Scoreboard() {
    delete this->tableWidget;
}

void Scoreboard::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe MainMenu #---------------------------------------#
   #-------------------------------------------------------------# */

MainMenu* MainMenu::instance = nullptr;

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();

    setCursor(Qt::PointingHandCursor);
    setFixedSize(400, 400);

    // Création du bouton pour démarrer le jeu
    QPushButton* playButton = new QPushButton("Jouer");
    connect(playButton, &QPushButton::clicked, this, &MainMenu::startGame);

    layout->addWidget(playButton);
    setLayout(layout);

    if (instance != nullptr) {
        delete instance;
    }

    instance = this;
}

MainMenu* MainMenu::getInstance(QWidget* parent) {
    if (instance == nullptr) {
        instance = new MainMenu(parent);
    }
    return instance;
}

void MainMenu::startGame() {
    // Lorsque le bouton "Jouer" est cliqué, ouvre la fenêtre du jeu
    Game* game = new Game();
    game->show();
    game->setFixedSize(400, 800);
    game->run();

    // Ferme le menu principal
    close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Game #-------------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Game::Game(QWidget* parent) : QGraphicsView(parent) {
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

/* <>---< Redirection vers le menu principal >---<> */
void Game::showMainMenu(){
    MainMenu* mainMenu = new MainMenu();
    mainMenu->show();

    // Ferme la fenêtre du jeu
    close();
}

/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
/* <>---< Gestion de la création des ennemis >---<> */
void Game::onCreateEnemy(){
    // On initialise de manière aléatoire la position latérale de l'alien
    int nPos;
    do {
        nPos = (rand() % SCREEN_WIDTH);
    } while (nPos < EntitySize.width() || nPos > SCREEN_WIDTH - EntitySize.width()); // On veut que l'alien soit dans l'écran

    // On veut que l'alien soit de couleur aléatoire
    int nColor = rand() % 3;
    // Création de l'alien, sa position est en dehors de l'écran (au dessus)
    Alien* pAlien = new Alien(static_cast<Color>(nColor));
    pAlien->setPos(nPos, this->myPlayer->y() - 800);
    // On ajoute l'alien à la scene
    scene()->addItem(pAlien);
    // On connecte l'alien aux conditions de défaite
    connect(pAlien, &Alien::sigDecreaseHealth, this, &Game::onDecreaseHealth);
    connect(pAlien, &Alien::sigGameOver, this, &Game::onGameOver);
}

/* <>---< Gestion de l'augmentation du score >---<> */
void Game::onIncreaseScore(){
    // TODO : Récupérer le score de l'alien pour l'ajouter au score du joueur
    playerPoints->increaseScore(50);
    isOver();
}

/* <>---< Gestion de la diminution des PVs >---<> */
void Game::onDecreaseHealth(){
    playerPoints->decreaseHealth();
    isOver();
}

/* <>---< Gestion de la fin du jeu >---<> */
void Game::onGameOver(){
    // TODO : Permettre au joueur d'entrer son nom, le stocker, afficher les meilleurs scores enregistrer et pouvoir relancer une partie
    MainMenu* mainMenu = MainMenu::getInstance();
    mainMenu->show();

    close();
}

/* <>---< Gestion des animations >---<> */
void Game::update() {
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
            spawnSpacing -= 175;
            break;
        }
    }


}

/* <-__---__---__---__---__--- Events ---__---__---__---__--- -> */
/* <>---< Gestion des évènements clavier >---<> */
void Game::keyPressEvent(QKeyEvent* event) {
    // Faire pause avec possibilité de reprendre
    if (event->key() == Qt::Key_P) {

        if (this->timer->isActive()) {
            // TODO : Afficher un menu de pause
            this->timer->stop();
            this->spawnTimer->stop();
            this->isMovingLeft = false;
            this->isMovingRight = false;
        }

        else {
            this->spawnTimer->start();
            this->timer->start();
        }
    }

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

//(-----------------------------------------Scoreboard-----------------------------------------)
Scoreboard::Scoreboard(QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);
    //donner un nom à la page
    setWindowTitle("Tableau de scores");
    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //this->background.load("../img/space-invader.jpg");
    //this->setSceneRect(0,0, background.width(), background.height());

    QWidget* centralWidget = new QWidget(this);
    //setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(5);
    tableWidget->setColumnCount(1);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(tableWidget);
    bestScoreLabel = new QLabel(this);
    bestScoreLabel->setText("Meilleur score : 0");
    bestScoreLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(bestScoreLabel);


    QStringList headerLabels;
    headerLabels << "Score";
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    QList<int> scores;
    scores << 100 << 200 << 150 << 120 << 180;

    int bestScore = 0;

    for (int row = 0; row < scores.size(); ++row) {
        int score = scores[row];
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(score));
        tableWidget->setItem(row, 0, item);

        if (score > bestScore) {
            bestScore = score;
        }
    }

    bestScoreLabel->setText("Meilleur score : " + QString::number(bestScore));

    tableWidget->resizeColumnsToContents();
}
void Scoreboard::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
Scoreboard::~Scoreboard() {
    delete this->tableWidget;
}