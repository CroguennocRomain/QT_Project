#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "settings.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QKeyEvent>

enum class Color { // Déclaration d'un type énuméré
    Red, Pink, Blue
};

class Bullet;

class Cannon : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    Cannon() : QGraphicsPixmapItem(QPixmap("../img/BlueCannon").scaled(50,50)) {};

    void shoot();

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

};

//////////////////////////////////////////////////////////////////////////

class Alien : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    Alien(Color Color, QGraphicsItem* parent = nullptr);

    Color getColor() const;
    void setColor(Color Color);

signals:
    void sigDecreaseHealth();
    void sigGameOver();

public slots:
    void onMove();

private:
    Color m_Color;
};

//////////////////////////////////////////////////////////////////////////

class Bullet : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    Bullet();

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

public slots:
    void onMove();

};

//////////////////////////////////////////////////////////////////////////

class Points : public QGraphicsTextItem {
Q_OBJECT
public:
    Points(QGraphicsItem* parent = nullptr);

    void increaseScore();
    void decreaseScore();
    void decreaseHealth();

    int getScore() const;
    int getHealth() const;

    void reset();

private:
    int m_nHealth = MaxHealth;
    int m_nScore  = 0;
};

#endif //TEST_COMPONENT_H
