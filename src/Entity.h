#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "settings.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Player #-----------------------------------------#
   #-------------------------------------------------------------# */

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Player() : QGraphicsPixmapItem(QPixmap("../img/Cannon").scaled(50,50)) {};

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void shoot();

signals:
/* <-__---__---__---__---__--- Signals ---__---__---__---__--- -> */
    void sigIncreaseScore();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Alien #------------------------------------------#
   #-------------------------------------------------------------# */
// TODO : Faire fonctionner les PVs et le score des Aliens
class Alien : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Alien(Color Color, QGraphicsItem* parent = nullptr);

/* <-__---__---__---__---__--- Getters ---__---__---__---__--- -> */
    Color getColor()  const;
    int   getPv()     const;
    int   getScore()  const;

/* <-__---__---__---__---__--- Setters ---__---__---__---__--- -> */
    void setColor(Color newColor);
    void setPv();
    void setScore();

signals:
/* <-__---__---__---__---__--- Signals ---__---__---__---__--- -> */
    void sigDecreaseHealth();
    void sigGameOver();

public slots:
/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
    void onMove();

private:
/* <-__---__---__---__---__--- Attributs ---__---__---__---__--- -> */
    Color m_Color;
    int PV;
    int score;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Bullet #-----------------------------------------#
   #-------------------------------------------------------------# */

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Bullet();

signals:
/* <-__---__---__---__---__--- Signals ---__---__---__---__--- -> */
    void sigIncreaseScore(int score);

public slots:
/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
    void onMove();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Points #-----------------------------------------#
   #-------------------------------------------------------------# */

class Points : public QGraphicsTextItem {
    Q_OBJECT

public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Points(QGraphicsItem* parent = nullptr);

/* <-__---__---__---__---__--- Getters  ---__---__---__---__--- -> */
    int getScore() const;
    int getHealth() const;

/* <-__---__---__---__---__--- Setters ---__---__---__---__--- -> */
    void increaseScore(int score);
    void decreaseHealth();

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void reset();

private:
/* <-__---__---__---__---__--- Attributs ---__---__---__---__--- -> */
    int m_nHealth;
    int m_nScore;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //TEST_COMPONENT_H