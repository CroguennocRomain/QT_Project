#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    /* On charge l'image de fond */
    //this->background.load("../img/espace.jpg");
    //this->setSceneRect(0, 0, background.width(), background.height());

    /* Méthodes d'ajout d'éléments à la scène -- tiré du sujet */
    QGraphicsRectItem* qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    QGraphicsTextItem* qgti = new QGraphicsTextItem("CIR2 Nantes");
    this->addItem(qgti);

    // ajout d'une entity
    this->entities.push_back(new Entity("../img/plane_blue.png"));
    this->addItem(this->entities[0]);

    /* Ajout du Timer pour l'animation */
    this->timer = new QTimer(this);
    this->timer->start(30); //toutes les 30 millisecondes
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


}

MyScene::~MyScene() {

}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MyScene::update() {
    for(Entity* entity : this->entities) {
        entity->move();
    }
}
