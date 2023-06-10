#ifndef CPP_QT_TPMINIPROJET_SCOREBOARD_H
#define CPP_QT_TPMINIPROJET_SCOREBOARD_H

#include "component.h"

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

    /* <-__---__---__---__---__--- Méthodes ---__---__---__---__--- -> */
};

#endif