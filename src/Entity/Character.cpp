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

/* #-------------------------------------------------------------#
   #---# Gestion des collisions  #-------------------------------#
   #-------------------------------------------------------------# */
void Character::defineHitBox() {
// Définition de la hitbox
    leftHitBox = new QGraphicsLineItem(0, 2, 0, this->pixmap().height() - 2, this);
    topHitBox = new QGraphicsLineItem(2, 0, this->pixmap().width() - 2, 0, this);
    rightHitBox = new QGraphicsLineItem(this->pixmap().width() - 1, 2, this->pixmap().width() - 1,
                                        this->pixmap().height() - 2, this);
    botHitBox = new QGraphicsLineItem(2, this->pixmap().height(), this->pixmap().width() - 2, this->pixmap().height(),
                                      this);

    this->leftHitBox->setOpacity(0);
    this->topHitBox->setOpacity(0);
    this->rightHitBox->setOpacity(0);
    this->botHitBox->setOpacity(0);
}

bool Character::collideHitBox(QGraphicsItem *item) {
// Détection de collision avec la hitbox
    if (this->leftHitBox->collidesWithItem(item) || this->topHitBox->collidesWithItem(item) || this->rightHitBox->collidesWithItem(item) || this->botHitBox->collidesWithItem(item)) {
        return true;
    }
    else {
        return false;
    }
}