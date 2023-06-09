#include "SpaceInvaders.h"
#include <QTimer>

SpaceInvaders::SpaceInvaders(QSize screenSize, QWidget* parent) : QGraphicsView(parent), m_screenSize(screenSize) {
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0, 0, m_screenSize.width(), m_screenSize.height());

    setBackgroundBrush(QBrush(QImage("../img/SpaceInvadersBg.jpg").scaled(m_screenSize)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void SpaceInvaders::run() {
    scene()->clear();
    setCursor(Qt::BlankCursor);

    m_pCannon = new Cannon();
    m_pCannon->setPos(m_screenSize.width() / 2, m_screenSize.height() - EntitySize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &Cannon::sigIncreaseScore, this, &SpaceInvaders::onIncreaseScore);
    connect(m_pCannon, &Cannon::sigDecreaseScore, this, &SpaceInvaders::onDecreaseScore);

    m_pPoints = new Points();
    scene()->addItem(m_pPoints);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &SpaceInvaders::onCreateEnemy);
    pTimer->start(2000);
}
void SpaceInvaders::checkPoints(){
    if(m_pPoints->getScore() < 0 || m_pPoints->getHealth() <= 0){
        m_pPoints->reset();
        onGameOver();
    }
}

void SpaceInvaders::keyPressEvent(QKeyEvent* pEvent) {
    if (m_pCannon == nullptr) {
        return;
    }

    switch (pEvent->key()) {
        case Qt::Key_Q:
            if (m_pCannon->x() > 0) {
                m_pCannon->setPos(m_pCannon->x() - 20, m_pCannon->y());
            }
            break;
        case Qt::Key_D:
            if (m_pCannon->x() + EntitySize.width() < m_screenSize.width()) {
                m_pCannon->setPos(m_pCannon->x() + 20, m_pCannon->y());
            }
            break;
        case Qt::Key_Space:
            m_pCannon->shoot();
            break;
    }

}

void SpaceInvaders::onCreateEnemy(){
    std::srand(time(0));
    int nPos = 100 + (rand() % m_screenSize.width() - 100);
    int nColor = rand() % 3;

    Alien* pAlien = new Alien(static_cast<Color>(nColor));
    pAlien->setPos(nPos, 0);

    scene()->addItem(pAlien);

    connect(pAlien, &Alien::sigDecreaseHealth, this, &SpaceInvaders::onDecreaseHealth);
    connect(pAlien, &Alien::sigGameOver, this, &SpaceInvaders::onGameOver);
}

void SpaceInvaders::onIncreaseScore(){
    m_pPoints->increaseScore();
    checkPoints();
}
void SpaceInvaders::onDecreaseScore(){
    m_pPoints->decreaseScore();
    checkPoints();
}
void SpaceInvaders::onDecreaseHealth(){
    m_pPoints->decreaseHealth();
    checkPoints();
}
void SpaceInvaders::onGameOver(){
     close();
}