#include "Character.h"

/* #-------------------------------------------------------------#
   #---# Gestion des déplacements  #-----------------------------#
   #-------------------------------------------------------------# */
void Character::moveTest() {
    QPointF pos = this->pos();
    this->setPos(pos.rx(), pos.ry() + 1);
}

void Character::moveUp() {
    // On récupère la position actuelle
    QPointF pos = this->pos();
    // On déplace le personnage vers le haut
    this->setPos(pos.rx(), pos.ry() - 1);
}

void Character::moveDown() {
    // On récupère la position actuelle
    QPointF pos = this->pos();
    // On déplace le personnage vers le bas
    this->setPos(pos.rx(), pos.ry() + 1);
}

void Character::moveLeft() {
    // On récupère la position actuelle
    QPointF pos = this->pos();
    // On déplace le personnage vers la gauche
    this->setPos(pos.rx() - 1, pos.ry());
}

void Character::moveRight() {
    // On récupère la position actuelle
    QPointF pos = this->pos();
    // On déplace le personnage vers la droite
    this->setPos(pos.rx() + 1, pos.ry());
}

