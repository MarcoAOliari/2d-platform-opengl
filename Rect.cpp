#include "Rect.h"

Rect::Rect(float width, float height, float x, float y, bool isArena) {
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->isArena = isArena;
}

bool Rect::getIsArena() {
    return this->isArena;
}