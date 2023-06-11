#ifndef TEST_SETTINGS_H
#define TEST_SETTINGS_H

/* <-__---__---__---__---__--- Bibliothèques ---__---__---__---__--- -> */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QtWidgets>

/* <-__---__---__---__---__--- Enumérations ---__---__---__---__--- -> */
/* <>---< Couleurs des Aliens >---<> */
enum class Color {
    Pink, Grenn, Blue, Yellow, Red,
};

/* <-__---__---__---__---__--- Constantes ---__---__---__---__--- -> */
/* <>---< Paramètres d'écran >---<> */
int   const SCREEN_WIDTH   = 400;
int   const SCREEN_HEIGHT  = 800;
QSize const ScreenSize     = QSize(SCREEN_WIDTH, SCREEN_HEIGHT);
/* <>---< Paramètres d'entités >---<> */
QSize const EntitySize     = QSize(50, 50);
int   const PlayerSpeed    = 10;
int   const BulletSpeed    = 5;
int   const AlienSpeed     = 13;
int   const AsteroidSpeed  = 30;
/* <>---< Paramètres de jeu >---<> */
int   const MaxHealth      = 3;
int   const ScrollingSpeed = 2;


#endif //TEST_SETTINGS_H