#include "Scoreboard.h"

Scoreboard::Scoreboard(QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);
    //donner un nom à la page
    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    this->background.load("../img/space-invader.jpg");
    this->setSceneRect(0,0, background.width(), background.height());

    // Création du tableau des scores
    this->tableWidget = new QTableWidget(10, 2, this);
}

void Scoreboard::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
Scoreboard::~Scoreboard() {
    delete this->tableWidget;
}