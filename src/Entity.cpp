#include "Entity.h"

void Entity::move() {
    this->setPos(this->x(), this->y() + this->speed);
}