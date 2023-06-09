#include "SpaceInvaders.h"
#include <QTimer>

SpaceInvaders::SpaceInvaders(QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    setBackgroundBrush(QBrush(QImage("../img/SpaceInvadersBg.jpg").scaled(ScreenSize)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(30);
}

void SpaceInvaders::run() {
    scene()->clear();
    setCursor(Qt::BlankCursor);

    m_pCannon = new Cannon();
    m_pCannon->setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT - EntitySize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &Cannon::sigIncreaseScore, this, &SpaceInvaders::onIncreaseScore);
    connect(m_pCannon, &Cannon::sigDecreaseScore, this, &SpaceInvaders::onDecreaseScore);

    m_pPoints = new Points();
    scene()->addItem(m_pPoints);

    this->spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout, this, &SpaceInvaders::onCreateEnemy);
    spawnTimer->start(2000);
}
void SpaceInvaders::checkPoints(){
    if(m_pPoints->getScore() < 0 || m_pPoints->getHealth() <= 0){
        m_pPoints->reset();
        onGameOver();
    }
}

void SpaceInvaders::onCreateEnemy(){
    std::srand(time(0));

    int nPos;
    do {
        nPos = (rand() % SCREEN_WIDTH);
    } while (nPos < EntitySize.width() || nPos > SCREEN_WIDTH - EntitySize.width());

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

void SpaceInvaders::update() {
    /* On gère les déplacements du personnage dans le update pour plus de fluidité */

    if (this->isMovingLeft) {
        if (m_pCannon->x() > 0) {
            m_pCannon->setPos(m_pCannon->x() - PlayerSpeed, m_pCannon->y());
        }
    }
    else if (this->isMovingRight) {
        if (m_pCannon->x() + EntitySize.width() < SCREEN_WIDTH) {
            m_pCannon->setPos(m_pCannon->x() + PlayerSpeed, m_pCannon->y());
        }
    }

    if (this->isMovingUp) {
        if (m_pCannon->y() > 0) {
            m_pCannon->setPos(m_pCannon->x(), m_pCannon->y() - PlayerSpeed);
        }
    }
    else if (this->isMovingDown) {
        if (m_pCannon->y() + EntitySize.height() < SCREEN_HEIGHT) {
            m_pCannon->setPos(m_pCannon->x(), m_pCannon->y() + PlayerSpeed);
        }
    }

}

void SpaceInvaders::keyPressEvent(QKeyEvent* event) {
    /* Faire pause avec possibilité de reprendre */
    if (event->key() == Qt::Key_P) {

        if (this->timer->isActive()) {
            this->timer->stop();
        }

        else {
            this->timer->start();
        }
    }

    /* Si le jeu n'est pas en pause on peut donc bouger */
    if (this->timer->isActive()) {
        // Bouger en haut
        if (event->key() == Qt::Key_Z) {
            this->isMovingUp = true;
        }

        // Bouger en bas
        if (event->key() == Qt::Key_S) {
            this->isMovingDown = true;
        }

        // Bouger à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = true;
        }

        // Bouger à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = true;
        }


    }
}

void SpaceInvaders::keyReleaseEvent(QKeyEvent *event) {
    /* Si le jeu n'est pas en pause on peut donc bouger */
    if (this->timer->isActive()) {
        // Bouger en haut
        if (event->key() == Qt::Key_Z) {
            this->isMovingUp = false;
        }

        // Bouger en bas
        if (event->key() == Qt::Key_S) {
            this->isMovingDown = false;
        }

        // Bouger à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = false;
        }

        // Bouger à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = false;
        }

        if (event->key() == Qt::Key_Space) {
            m_pCannon->shoot();
        }

    }
}