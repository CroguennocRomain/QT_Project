#ifndef TEST_SPACEINVADERS_H
#define TEST_SPACEINVADERS_H

#include "component.h"

class SpaceInvaders : public QGraphicsView {
Q_OBJECT
public:
    SpaceInvaders(QWidget* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    void drawBackground(QPainter* painter, const QRectF& rect);
    void run();
    void checkPoints();

protected:
    void keyPressEvent(QKeyEvent* pEvent) override;
    void keyReleaseEvent(QKeyEvent* pEvent) override;

public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseHealth();
    void onGameOver();

    void update();

private:
    QPixmap    background;
    QTimer*    timer;
    QTimer*    spawnTimer;
    Player*    myPlayer = nullptr;
    Points*    playerPoints = nullptr;
    int        m_Scrolling = ScrollingSpeed;
    int        m_BackgroundPosY = 0;

    /* Paramètres de gestion des déplacement */
    bool isMovingLeft = false;
    bool isMovingRight = false;
};


#endif //TEST_SPACEINVADERS_H
