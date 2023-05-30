#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include "Entity/Character.h"

#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QRectF>

class MyScene : public QGraphicsScene {
Q_OBJECT

private :
    QPixmap background;
    QTimer* timer;

    Character* player;
    QVector<Character*> enemies;

    /* Paramètres de gestion des déplacement */
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;

public:
    /* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    MyScene(QObject* parent = nullptr);

    /* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
    virtual ~MyScene();

    /* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void drawBackground(QPainter* painter, const QRectF& rect);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void update();
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
