#include "SpaceInvaders.h"

SpaceInvaders::SpaceInvaders(QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* pScene = new QGraphicsScene();

    setScene(pScene);

    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    this->background.load("../img/BackGround.jpg");
    this->setSceneRect(0,0, background.width(), background.height());

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");

    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(30);

}

void SpaceInvaders::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void SpaceInvaders::run() {
    scene()->clear();
    setCursor(Qt::BlankCursor);

    myPlayer = new Player();
    myPlayer->setPos( (SCREEN_WIDTH - EntitySize.width()) / 2 , 500 - (EntitySize.height()/2) ); //2800
    // Permet de gérer les évènements clavier
    myPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    myPlayer->setFocus();
    scene()->addItem(myPlayer);

    connect(myPlayer, &Player::sigIncreaseScore, this, &SpaceInvaders::onIncreaseScore);

    playerPoints = new Points();
    scene()->addItem(playerPoints);

    /*
    this->spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout, this, &SpaceInvaders::onCreateEnemy);
    spawnTimer->start(2000);
    */
}
void SpaceInvaders::checkPoints(){
    if(playerPoints->getScore() < 0 || playerPoints->getHealth() <= 0){
        playerPoints->reset();
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
    pAlien->setPos(nPos, this->myPlayer->y() - 800);

    scene()->addItem(pAlien);

    connect(pAlien, &Alien::sigDecreaseHealth, this, &SpaceInvaders::onDecreaseHealth);
    connect(pAlien, &Alien::sigGameOver, this, &SpaceInvaders::onGameOver);
}

void SpaceInvaders::onIncreaseScore(){
    playerPoints->increaseScore(50);
    checkPoints();
}

void SpaceInvaders::onDecreaseHealth(){
    playerPoints->decreaseHealth();
    checkPoints();
}
void SpaceInvaders::onGameOver(){
     close();
}

void SpaceInvaders::update() {

    if (myPlayer != nullptr) {
        QPointF target(myPlayer->x() + EntitySize.width() / 2, myPlayer->y() + EntitySize.height() / 2 - 300);
        centerOn(target);
    }

    /* On gère les déplacements du vaisseau dans le update pour plus de fluidité */
    if (this->isMovingLeft) {
        if (myPlayer->x() > 0) {
            myPlayer->setPos(myPlayer->x() - PlayerSpeed, myPlayer->y());
        }
    }
    else if (this->isMovingRight) {
        if (myPlayer->x() + EntitySize.width() < SCREEN_WIDTH) {
            myPlayer->setPos(myPlayer->x() + PlayerSpeed, myPlayer->y());
        }
    }


    myPlayer->setPos(myPlayer->x(), myPlayer->y() - m_Scrolling);
    playerPoints->setPos(0, myPlayer->y()-675);

    if(myPlayer->y() <= 400-m_Scrolling-(EntitySize.height()/2) + 300){ // MODIFIER POUR QU'IL N'Y AIT PAS DE TP
        myPlayer->setPos(myPlayer->x(), myPlayer->y()+2400- 300);
        //m_Scrolling = 0;
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

        // Bouger à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = true;
        }

        // Bouger à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = true;
        }

        // Tirer
        if (event->key() == Qt::Key_Space) {
            myPlayer->shoot();
        }

    }
}

void SpaceInvaders::keyReleaseEvent(QKeyEvent *event) {
    /* Si le jeu n'est pas en pause on peut donc bouger */
    if (this->timer->isActive()) {

        // Bouger à gauche
        if (event->key() == Qt::Key_Q) {
            this->isMovingLeft = false;
        }

        // Bouger à droite
        if (event->key() == Qt::Key_D) {
            this->isMovingRight = false;
        }



    }
}