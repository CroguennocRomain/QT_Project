#ifndef QT_PROJECT_ENTITY_H
#define QT_PROJECT_ENTITY_H

#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Entity : public QGraphicsPixmapItem {

private :
    int speed;

public:

    /* Constructeur */
    Entity(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)) {
        this->speed = 10;
    }

    /* Getters & Setters */
    int getSpeed() const { return this->speed; }
    void setSpeed(int new_speed) { this->speed = new_speed; }

    /* Méthodes */
    void move();
    void keyPressEvent(QKeyEvent* event);
};


#endif //QT_PROJECT_ENTITY_H