#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include "Entity.h"

#include <QPixmap>
#include <QTimer>
#include <QPainter>

class MyScene : public QGraphicsScene {
    Q_OBJECT

private :
    QPixmap background;
    QTimer* timer;
    QVector<Entity*> entities;

public:
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();

};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
