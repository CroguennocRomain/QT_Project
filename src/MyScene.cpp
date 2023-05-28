#include "MyScene.h"

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    /* On crée le joueur */
    this->player = new Character("../img/emoji_caca.png");
    this->player->setPos(200, 700);
    this->addItem(player);

    /* On charge l'image de fond */
    //this->background.load("../img/espace.jpg");
    //this->setSceneRect(0, 0, background.width(), background.height());

    /* Méthodes d'ajout d'éléments à la scène -- tiré du sujet */
    QGraphicsRectItem* qgri = new QGraphicsRectItem(0, 0, 400, 800);
    this->addItem(qgri);

    QGraphicsTextItem* qgti = new QGraphicsTextItem("CIR2 Nantes");
    this->addItem(qgti);

    /* Ajout du Timer pour l'animation */
    this->timer = new QTimer(this);
    this->timer->start(30); //toutes les 30 millisecondes
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

}

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
MyScene::~MyScene() {

    delete this->player;
    delete this->timer;

}

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */

/* #-------------------------------------------------------------#
   #---# Gestion de l'affichage de la scène #--------------------#
   #-------------------------------------------------------------# */
void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

/* #-------------------------------------------------------------#
   #---# Gestion de l'animation de la scène // fonction update #-#
   #-------------------------------------------------------------# */
void MyScene::update() {

    //player->moveTest();

    /* On gère les déplacements du personnage dans le update pour plus de fluidité */

    if (this->isMovingUp) {
        this->player->moveUp();
    }
    else if (this->isMovingDown) {
        this->player->moveDown();
    }
    else if (this->isMovingLeft) {
        this->player->moveLeft();
    }
    else if (this->isMovingRight) {
        this->player->moveRight();
    }

}

/* #-------------------------------------------------------------#
   #---# Gestion des touches du clavier #------------------------#
   #-------------------------------------------------------------# */
void MyScene::keyPressEvent(QKeyEvent* event) {
    /* Faire pause avec possibilité de reprendre */
    if (event->key() == Qt::Key_P) {

        if (this->timer->isActive()) {
            this->timer->stop();
        }

        else {
            this->timer->start();
        }
    }

    /* Si le jeu n'est pas en pause on peut donc bouger */
    if (this->timer->isActive()) {
        // Bouger en haut
        if (event->key() == Qt::Key_Z) {
            this->isMovingUp = true;
        }

        // Bouger en bas
        if (event->key() == Qt::Key_S) {
            this->isMovingDown = true;
        }

        // Bouger à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = true;
        }

        // Bouger à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = true;
        }

    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event) {
    /* Si le jeu n'est pas en pause on peut donc bouger */
    if (this->timer->isActive()) {
        // Bouger en haut
        if (event->key() == Qt::Key_Z) {
            this->isMovingUp = false;
        }

        // Bouger en bas
        if (event->key() == Qt::Key_S) {
            this->isMovingDown = false;
        }

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