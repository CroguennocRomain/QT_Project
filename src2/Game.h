#ifndef TEST_Game_H
#define TEST_Game_H

#include "component.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Game #-------------------------------------------#
   #-------------------------------------------------------------# */
class Game : public QGraphicsView {
    Q_OBJECT
private:
/* <-__---__---__---__---__--- Attributs ---__---__---__---__--- -> */
/* <>---< Gestion de la scène et du jeu >---<> */
    QPixmap       background;
    QTimer*       timer;
    QTimer*       spawnTimer;
    int           m_Scrolling = ScrollingSpeed;
    int           spawnSpacing = 3000;
    QVector<bool> spaceSwpan = {false, false, false, false, false, false, false, false, false, false};

/* <>---< Gestion des composants >---<> */
    Player*       myPlayer = nullptr;
    Points*       playerPoints = nullptr;

/* <>---< Gestion des déplacements >---<> */
    bool          isMovingLeft = false;
    bool          isMovingRight = false;

public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Game(QWidget* parent = nullptr);

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
    ~Game();

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void run();
    void isOver();

protected:
/* <-__---__---__---__---__--- Events ---__---__---__---__--- -> */
    void keyPressEvent(QKeyEvent* pEvent) override;
    void keyReleaseEvent(QKeyEvent* pEvent) override;

public slots:
/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseHealth();
    void onGameOver();

    void update();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //TEST_Game_H