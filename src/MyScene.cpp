#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    // On charge l'image de fond
    this->background.load("../img/espace.jpg");
    this->setSceneRect(0, 0, background.width(), background.height());

}

MyScene::~MyScene() {

}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
