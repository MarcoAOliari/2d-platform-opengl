#include "Character.h"
#include "utils.h"
#include <iostream>

using namespace std;

Character::Character(Circle c, Rect arena, float larguraTotal) {
    gX = larguraTotal * (c.cx - arena.x) / arena.width;

    float y = 500 * (c.cy - arena.y) / arena.height;
    float r = 500 * c.r / arena.height;

    gY = y - 0.75 * r;
    raioCabeca = 0.25 * r;
    alturaQuadril = 0.66666 * r;
    alturaArticulacao = 0.2083333 * r;
    gThetaQuadril1 = 0; 
    gThetaQuadril2 = 0; 
    gThetaJoelho1 = 0;
    gThetaJoelho2 = 0;

    // cout << gX << " " << gY << "\n";
}

void Character::DesenhaTronco() {
    glPushMatrix();
    glTranslatef(-0.8*this->raioCabeca, this->raioCabeca, 0);
    DesenhaRect(1.6 * this->raioCabeca, this->alturaQuadril, 0, 1, 0);
    glPopMatrix();
}

void Character::Desenha() {
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);
    DesenhaCirc(this->raioCabeca, 0, 1, 0);
    this->DesenhaTronco();
    glPopMatrix();
}