#include "Character.h"

void Character::move() {
    QPointF pos = this->pos();
    this->setPos(pos.rx(), pos.ry()+1);
}