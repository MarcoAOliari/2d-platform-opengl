#include "Obstacle.h"
#include "utils.h"
#include <iostream>

using namespace std;

Obstacle::Obstacle(Rect r, Rect arena, float larguraTotal) {
    this->height = 500 * r.height / arena.height;
    this->width = larguraTotal * r.width / arena.width;
    this->gX = larguraTotal * (r.x - arena.x) / arena.width + this->width * 0.5;
    this->gY = 500 * (r.y - arena.y) / arena.height;
}

void Obstacle::Desenha() {
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);
    DesenhaRect(this->width, this->height, 0, 0, 0);
    glPopMatrix();
}