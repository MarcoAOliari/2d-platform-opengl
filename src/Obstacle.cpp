#include "../header/Obstacle.h"
#include "../header/utils.h"
#include <iostream>

using namespace std;

Obstacle::Obstacle(Rect r, Rect arena, float larguraTotal) {
    this->height = 500 * r.height / arena.height;
    this->width = larguraTotal * r.width / arena.width;
    this->gX = larguraTotal * (r.x - arena.x) / arena.width + this->width * 0.5;
    this->gY = 500 * (r.y - arena.y) / arena.height;
}

Obstacle::Obstacle(float larguraTotal) {
    this->height = 500;
    this->width = larguraTotal;
    this->gX = larguraTotal / 2.0;
    this->gY = 500;
}

void Obstacle::Desenha() {
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);
    DesenhaRect(this->width, this->height, 0, 0, 0);
    glPopMatrix();
}

GLfloat Obstacle::getgX() {
    return this->gX;
}

GLfloat Obstacle::getgY() {
    return this->gY;
}

GLfloat Obstacle::getWidth() {
    return this->width;
}

GLfloat Obstacle::getHeight() {
    return this->height;
}
