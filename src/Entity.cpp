#include "Entity.h"

void Entity::move() {
    QPointF pos = this->pos();
    this->setPos(pos.rx(), pos.ry()+1);
}


void Entity::keyPressEvent(QKeyEvent* event) {
    QPointF pos = this->pos();

    /* Déplacement vers le haut */
    if (event->key() == Qt::Key_Z) {
        this->setPos(pos.rx(), pos.ry()-10);
    }

    /* Déplacement vers le bas */
    if (event->key() == Qt::Key_S) {
        this->setPos(pos.rx(), pos.ry()+10);
    }

    /* Déplacement vers la gauche */
    if (event->key() == Qt::Key_Q) {
        this->setPos(pos.rx()-10, pos.ry());
    }

    /* Déplacement vers la droite */
    if (event->key() == Qt::Key_D) {
        this->setPos(pos.rx()+10, pos.ry());
    }

}