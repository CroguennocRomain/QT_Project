#ifndef QT_PROJECT_CHARACTER_H
#define QT_PROJECT_CHARACTER_H


#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Character : public QGraphicsPixmapItem {

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

};


#endif //QT_PROJECT_CHARACTER_H
