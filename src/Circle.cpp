#include "../header/Circle.h"

Circle::Circle(float cx, float cy, float r, bool isPlayer) {
    this->cx = cx;
    this->cy = cy;
    this->r = r;
    this->isPlayer = isPlayer;
}

bool Circle::getIsPlayer() {
    return this->isPlayer;
}