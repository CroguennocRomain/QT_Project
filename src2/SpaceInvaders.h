#ifndef TEST_SPACEINVADERS_H
#define TEST_SPACEINVADERS_H

#include "component.h"

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>

class SpaceInvaders : public QGraphicsView {
Q_OBJECT
public:
    SpaceInvaders(QWidget* parent = nullptr);

    void run();
    void checkPoints();

protected:
    void keyPressEvent(QKeyEvent* pEvent) override;
    void keyReleaseEvent(QKeyEvent* pEvent) override;

public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseScore();
    void onDecreaseHealth();
    void onGameOver();

    void update();

private:
    QTimer*    timer;
    QTimer*    spawnTimer;
    Cannon*    m_pCannon = nullptr;
    Points*    m_pPoints = nullptr;

    /* Paramètres de gestion des déplacement */
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
};


#endif //TEST_SPACEINVADERS_H
