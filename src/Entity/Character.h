#ifndef QT_PROJECT_ENTITY_H
#define QT_PROJECT_ENTITY_H

#include <iostream>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointF>

class Character : public QGraphicsPixmapItem {

private :
    int speed;

public:

    /* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Character(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName).scaled(50,50)) {
        this->speed = 10;
    }

    /* <-__---__---__---__---__--- Getters et setters ---__---__---__---__--- -> */
    int getSpeed() const { return this->speed; }
    void setSpeed(int new_speed) { this->speed = new_speed; }

    /* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void moveTest();
    /* Gestion des déplacements simples */
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();



};


#endif //QT_PROJECT_ENTITY_H