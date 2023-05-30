#ifndef QT_PROJECT_ENTITY_H
#define QT_PROJECT_ENTITY_H

// Variables globales
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 800

#include <iostream>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointF>


class Character : public QGraphicsPixmapItem {

private :
    QGraphicsLineItem* leftHitBox;
    QGraphicsLineItem* topHitBox;
    QGraphicsLineItem* rightHitBox;
    QGraphicsLineItem* botHitBox;

    int speed;
    int pv = 3;
public:

    /* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Character(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName).scaled(50,50)) {
        this->speed = 4;

        this->defineHitBox();
    }

    /* <-__---__---__---__---__--- Getters et setters ---__---__---__---__--- -> */
    int getSpeed() const { return this->speed; }
    void setSpeed(int new_speed) { this->speed = new_speed; }

    int getPV() const { return this->pv; }
    void setPV(int new_pv) { this->pv = new_pv; }

    /* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void moveTest();
    /* Gestion des déplacements simples */
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    /* Gestion des collisions */
    void defineHitBox();
    bool collideHitBox(QGraphicsItem* item);
    /* Gestion de la sortie de l'écran */
    void checkOutOfScreen();
    void checkOutOfScreenLeft();
    void checkOutOfScreenRight();
    void checkOutOfScreenTop();
    void checkOutOfScreenBot();



};


#endif //QT_PROJECT_ENTITY_H