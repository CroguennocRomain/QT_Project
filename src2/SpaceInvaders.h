#ifndef TEST_SPACEINVADERS_H
#define TEST_SPACEINVADERS_H

#include "component.h"

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>

class SpaceInvaders : public QGraphicsView {
Q_OBJECT
public:
    SpaceInvaders(QSize screenSize, QWidget* parent = nullptr);

    void run();
    void checkPoints();

protected:
    void keyPressEvent(QKeyEvent* pEvent) override;

public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseScore();
    void onDecreaseHealth();
    void onGameOver();

private:
    Cannon*    m_pCannon = nullptr;
    Points*    m_pPoints = nullptr;
    QSize       m_screenSize;
};


#endif //TEST_SPACEINVADERS_H
