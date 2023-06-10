#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "component.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe ButtonPanel #------------------------------------#
   #-------------------------------------------------------------# */

class ButtonPanel : public QWidget {
Q_OBJECT
public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    ButtonPanel(QWidget *parent = nullptr);

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
    ~ButtonPanel();

/* <-__---__---__---__---__--- Getters ---__---__---__---__--- -> */
    QString getPlayerName() const;

private:
/* <-__---__---__---__---__--- Attributs ---__---__---__---__--- -> */
    QPushButton *startButton;
    QPushButton *quitButton;
    QLineEdit   *textInput;
    QString     playerName;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe Scoreboard #-------------------------------------#
   #-------------------------------------------------------------# */

class Scoreboard : public QGraphicsView {
Q_OBJECT

private:
    QPixmap background;
    QTableWidget* tableWidget;
    QLabel* bestScoreLabel;

public:


    /* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Scoreboard(QWidget* parent = nullptr);
    void setupTable();
    void drawBackground(QPainter* painter, const QRectF& rect);
    /* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
    virtual ~Scoreboard();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* #-------------------------------------------------------------#
   #---# Classe MainMenu #---------------------------------------#
   #-------------------------------------------------------------# */

class MainMenu : public QWidget {
Q_OBJECT
public:
    MainMenu(QWidget* parent = nullptr);

private:
    ButtonPanel*  buttonPanel;
    Scoreboard*   scoreboard;

public slots:
/* <-__---__---__---__---__--- Slots ---__---__---__---__--- -> */
/* <>---< Gestion du jeu >---<> */
    void startGame();
/* <>---< Gestion des menus >---<> */
    void slot_aboutMenu();
    void slot_commandeMenu();
    void slot_reglesMenu();
};

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
    int           spawnSpacing = 1500;
    bool          over = false;
    QVector<bool> spaceSwpan = {false, false, false, false, false, false, false, false, false, false};
    QString       playerName;

/* <>---< Gestion des composants >---<> */
    Player*       myPlayer = nullptr;
    Points*       playerPoints = nullptr;

/* <>---< Gestion des déplacements >---<> */
    bool          isMovingLeft = false;
    bool          isMovingRight = false;

public:
/* <-__---__---__---__---__--- Constructeur ---__---__---__---__--- -> */
    Game(QString playerName, QWidget* parent = nullptr);

/* <-__---__---__---__---__--- Destructeur ---__---__---__---__--- -> */
    ~Game();

/* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void run();
    void isOver();
    void addDataToCSV(QString playerName, int score);

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