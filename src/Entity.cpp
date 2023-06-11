#include "Entity.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Player #-----------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
/* <>---< Gestion du tir >---<> */
void Player::shoot()
{
    // Création du projectile
    Bullet* pBullet = new Bullet();
    connect(pBullet, &Bullet::sigIncreaseScore, this, &Player::sigIncreaseScore);
    // On place le projectile au niveau du canon du vaisseau
    pBullet->setPos(x() + 13, y() - 5);
    scene()->addItem(pBullet);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Alien #------------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Alien::Alien(Color Color, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    // Initialisation des attributs
    setColor(Color);
    setPv();
    setScore();

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &Alien::onMove);
    pTimer->start(50);
}

/* <-__---__---__---__---__--- Getters ---__---__---__---__--- -> */
/* <>---< Gestion de la couleur >---<> */
Color Alien::getColor() const
{
    return this->m_Color;
}

/* <>---< Gestion des points de vie >---<> */
int Alien::getPv() const
{
    return this->PV;
}

/* <>---< Gestion des points de score >---<> */
int Alien::getScore() const
{
    return this->score;
}

/* <-__---__---__---__---__--- Setters ---__---__---__---__--- -> */
/* <>---< Gestion de la couleur >---<> */
void Alien::setColor(Color newColor)
{
    this->m_Color = newColor;

    switch (this->getColor()) {

        case Color::Pink:
            setPixmap(QPixmap("../img/AlienPink.png").scaled(EntitySize));
            break;
        case Color::Grenn:
            setPixmap(QPixmap("../img/AlienGreen.png").scaled(EntitySize));
            break;
        case Color::Blue:
            setPixmap(QPixmap("../img/AlienBlue.png").scaled(EntitySize));
            break;
        case Color::Yellow:
            setPixmap(QPixmap("../img/AlienYellow.png").scaled(EntitySize));
            break;
        case Color::Red:
            setPixmap(QPixmap("../img/AlienRed.png").scaled(EntitySize));
            break;

    }
}

/* <>---< Gestion des points de vie >---<> */
void Alien::setPv()
{
    switch (this->getColor()) {

            case Color::Pink:
                this->PV = 1;
                break;
            case Color::Grenn:
                this->PV = 2;
                break;
            case Color::Blue:
                this->PV = 3;
                break;
            case Color::Yellow:
                this->PV = 4;
                break;
            case Color::Red:
                this->PV = 5;
                break;

    }
}

/* <>---< Gestion des points de score >---<> */
void Alien::setScore()
{
    switch (this->getColor()) {

            case Color::Pink:
                this->score = 20;
                break;
            case Color::Grenn:
                this->score = 40;
                break;
            case Color::Blue:
                this->score = 60;
                break;
            case Color::Yellow:
                this->score = 80;
                break;
            case Color::Red:
                this->score = 100;
                break;

    }
}

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
/* <>---< Gestion du déplacement >---<> */
void Alien::onMove()
{
    setPos(x(), y() + AlienSpeed);

    /* <>---< Gestion de la collision avec le joueur >---<> */
    QList<QGraphicsItem*> lstCollidingItems = collidingItems();
    /* Si l'Alien touche le joueur c'est la fin */
    for (auto const pItem : lstCollidingItems) {
        if (dynamic_cast<Player*>(pItem)) {
            emit sigGameOver();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Bullet #-----------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Bullet::Bullet() : QGraphicsPixmapItem(QPixmap("../img/Bullet").scaled(20,20))
{
    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &Bullet::onMove);
    pTimer->start(BulletSpeed);
}

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
/* <>---< Gestion du déplacement >---<> */
void Bullet::onMove()
{
    /* <>---< Gestion des collisions >---<> */
    QList<QGraphicsItem*> lstCollidingItems = collidingItems();
    /* Si le projectile touche un Alien il est supprimé et le score augmente */
    for(auto const pItem : lstCollidingItems) {
        Alien* pAlien = dynamic_cast<Alien*>(pItem);
        if(pAlien != nullptr) {

            scene()->removeItem(pAlien);
            scene()->removeItem(this);

            emit sigIncreaseScore(pAlien->getScore());

            delete pAlien;
            delete this;

            return;
        }
    }

    setPos(x(), y() - 10);

    if(pos().y() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Points #-----------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Points::Points(QGraphicsItem *parent) : QGraphicsTextItem(){
    this->m_nScore = 0;
    this->m_nHealth = MaxHealth;

    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

/* <-__---__---__---__---__--- Getters ---__---__---__---__--- -> */
/* <>---< Gestion des points de score >---<> */
int Points::getScore() const
{
    return m_nScore;
}

/* <>---< Gestion des points de vie >---<> */
int Points::getHealth() const
{
    return m_nHealth;
}

/* <-__---__---__---__---__--- Setters ---__---__---__---__--- -> */
void Points::increaseScore(int score)
{
    m_nScore += score;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

void Points::decreaseHealth()
{
    m_nHealth -= 1;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
void Points::reset() {
    m_nScore = 0;
    m_nHealth = AlienSpeed;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Asteroid #---------------------------------------#
   #-------------------------------------------------------------# */

/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
Asteroid::Asteroid(bool sideLeft, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    /* <>---< Gestion du sens >---<> */
    setSideLeft(sideLeft);
    if (isLeft) {
        setPixmap(QPixmap("../img/AsteroidLeft").scaled(EntitySize));
    } else {
        setPixmap(QPixmap("../img/AsteroidRight").scaled(EntitySize));
    }

    /* <>---< Gestion du déplacement >---<> */
    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &Asteroid::onMove);
    pTimer->start(50);
}

/* <-__---__---__---__---__--- Getters ---__---__---__---__--- -> */
/* <>---< Gestion du sens >---<> */
bool Asteroid::getSideLeft() const
{
    return isLeft;
}

/* <-__---__---__---__---__--- Setters ---__---__---__---__--- -> */
/* <>---< Gestion du sens >---<> */
void Asteroid::setSideLeft(bool sideLeft)
{
    isLeft = sideLeft;
}


/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
/* <>---< Gestion du déplacement >---<> */
void Asteroid::onMove()
{
    std::cout << "Asteroid::onMove()" << std::endl;
    /* <>---< Gestion du sens >---<> */
    if (getSideLeft()) {
        setPos(x() + AsteroidSpeed, y() + AsteroidSpeed);
    } else {
        setPos(x() - AsteroidSpeed, y() + AsteroidSpeed);
    }

    /* <>---< Gestion de la collision avec le joueur >---<> */
    QList<QGraphicsItem*> lstCollidingItems = collidingItems();
    /* Si l'Astéroïde touche le joueur c'est la fin */
    for (auto const pItem : lstCollidingItems) {
        if (dynamic_cast<Player*>(pItem)) {
            emit sigGameOver();
        }
    }
}

