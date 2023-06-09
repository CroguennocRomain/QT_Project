#include "component.h"

#include <QTimer>
#include <QGraphicsScene>


void Cannon::shoot()
{
    Bullet* pBullet = new Bullet();
    connect(pBullet, &Bullet::sigIncreaseScore, this, &Cannon::sigIncreaseScore);
    connect(pBullet, &Bullet::sigDecreaseScore, this, &Cannon::sigDecreaseScore);

    pBullet->setPos(x() + 13, y() - 5);
    scene()->addItem(pBullet);
}

//////////////////////////////////////////////////////////////////////////

Alien::Alien(Color Color, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setColor(Color);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &Alien::onMove);
    pTimer->start(AlienSpeed);
}

Color Alien::getColor() const
{
    return m_Color;
}

void Alien::setColor(Color Color)
{
    m_Color = Color;

    switch (m_Color) {
        case Color::Red:
            setPixmap(QPixmap("../img/RedAlien.png").scaled(EntitySize));
            break;
        case Color::Pink:
            setPixmap(QPixmap("../img/PinkAlien.png").scaled(EntitySize));
            break;
        case Color::Blue:
            setPixmap(QPixmap("../img/BlueAlien.png").scaled(EntitySize));
            break;
        default:
            setPixmap(QPixmap("../img/RedAlien.png").scaled(EntitySize));

    }
}

void Alien::onMove()
{
    setPos(x(), y() + 5);

    if (pos().y() >= scene()->height() - EntitySize.height()) {
        scene()->removeItem(this);
        emit sigDecreaseHealth();
        delete this;
    }

    QList<QGraphicsItem*> lstCollidingItems = collidingItems();

    for (auto const pItem : lstCollidingItems) {
        if (dynamic_cast<Cannon*>(pItem)) {
            emit sigGameOver();
        }
    }
}

//////////////////////////////////////////////////////////////////////////

Bullet::Bullet() : QGraphicsPixmapItem(QPixmap("../img/BlueBullet").scaled(20,20))
{


    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &Bullet::onMove); //
    pTimer->start(BulletSpeed);
}


void Bullet::onMove()
{
    QList<QGraphicsItem*> lstCollidingItems = collidingItems();

    for(auto const pItem : lstCollidingItems) {
        Alien* pAlien = dynamic_cast<Alien*>(pItem);
        if(pAlien != nullptr) {

            scene()->removeItem(pAlien);
            scene()->removeItem(this);

            emit sigIncreaseScore();

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

//////////////////////////////////////////////////////////////////////////

Points::Points(QGraphicsItem *parent) : QGraphicsTextItem(){
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

void Points::increaseScore()
{
    m_nScore += 50;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

void Points::decreaseScore()
{
    m_nScore -= 50;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

void Points::decreaseHealth()
{
    m_nHealth -= 1;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

int Points::getScore() const
{
    return m_nScore;
}

int Points::getHealth() const
{
    return m_nHealth;
}

void Points::reset() {
    m_nScore = 0;
    m_nHealth = AlienSpeed;
    setPlainText(QString("Score: ") + QString::number(m_nScore) + "\n"
                    + QString("Health: ") + QString::number(m_nHealth));
}

//////////////////////////////////////////////////////////////////////////