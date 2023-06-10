#ifndef TEST_SETTINGS_H
#define TEST_SETTINGS_H

#include <iostream>

#include <QtWidgets>

enum class Color {
    Pink, Blue, Red,
};

/*
enum class Color {
    Pink, Grenn, Blue, Yellow, Red,
};
 */

int   const SCREEN_WIDTH   = 400;
int   const SCREEN_HEIGHT  = 800;
QSize const ScreenSize     = QSize(SCREEN_WIDTH, SCREEN_HEIGHT);
QSize const EntitySize     = QSize(50, 50);
int   const PlayerSpeed    = 10;
int   const BulletSpeed    = 5;
int   const AlienSpeed     = 50;
int   const MaxHealth      = 3;
int   const ScrollingSpeed = 2;


#endif //TEST_SETTINGS_H