#include "Entity.h"

void Entity::move() {
    QPointF pos = this->pos();
    this->setPos(pos.rx(), pos.ry()+1);
}