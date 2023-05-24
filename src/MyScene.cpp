#include "MyScene.h"

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    this->background.load("emoji_caca.png");
    QGraphicsRectItem* qgri = new QGraphicsRectItem(10, 100, 300, 200);
    this->addItem(qgri);

    QGraphicsTextItem* qgti = new QGraphicsTextItem("CIR2 Nantes");
    this->addItem(qgti);

    // créer un objet de type QGraphicsPixmapItem
    QGraphicsPixmapItem* qgpi = new QGraphicsPixmapItem(QPixmap("img/emoji_caca.png"));
    // ajouter l'objet à la scène
    this->addItem(qgpi);



}

MyScene::~MyScene() {

}
