#ifndef QT_PROJECT_PROJECTILE_H
#define QT_PROJECT_PROJECTILE_H

#include <iostream>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointF>

class Projectile : public QGraphicsPixmapItem {

private :
    int speed;
    bool isEnemy;
public:
    /* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Projectile(QString imageFileName, bool isEnemy) : QGraphicsPixmapItem(QPixmap(imageFileName)) {
        this->speed = 10;
        this->isEnemy = isEnemy;
    }

    /* <-__---__---__---__---__--- Getters et setters ---__---__---__---__--- -> */
    int getSpeed() const { return this->speed; }
    void setSpeed(int new_speed) { this->speed = new_speed; }

    bool getIsEnemy() const { return this->isEnemy; }
    void setIsEnemy(bool new_isEnemy) { this->isEnemy = new_isEnemy; }

    /* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */

    /* Gestion des déplacements simples */
    void moveUp();
    void moveDown();
    /* Gestion des collisions */
    void defineHitBox();
    bool collideHitBox(QGraphicsItem* item);
};


#endif //QT_PROJECT_PROJECTILE_H
