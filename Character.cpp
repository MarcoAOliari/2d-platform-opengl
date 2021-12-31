#include "Character.h"
#include "utils.h"
#include <iostream>
#define PI 3.14159264

using namespace std;

Character::Character(Circle c, Rect arena, float larguraTotal) {
    gX = larguraTotal * (c.cx - arena.x) / arena.width /*+ 100 */;

    float y = 500 * (c.cy - arena.y) / arena.height /* -  100 */;
    float r = 500 * c.r / arena.height /* + 50 */;

    gY = y - 0.75 * r;
    raioCabeca = 0.25 * r;
    alturaQuadril = 0.7 * r;
    larguraQuadril = 0.7 * raioCabeca;
    alturaArticulacao = 0.43333 * r;
    larguraArticulacao = 0.4 * raioCabeca;
    gThetaQuadril1 = 60; 
    gThetaQuadril2 = 100; 
    gThetaJoelho1 = 30;
    gThetaJoelho2 = 0;
}

void Character::DesenhaTronco() {
    glTranslatef(0, this->raioCabeca, 0);
    DesenhaRect(this->larguraQuadril, this->alturaQuadril, 0, 1, 0);
}

void Character::DesenhaCoxa(int id) {
    if (id == 1) {
        glRotatef(this->gThetaQuadril1, 0, 0, 1);
    } else if (id == 2) {
        glRotatef(this->gThetaQuadril2, 0, 0, 1);
    }

    // correcao pra juntar joelho
    DesenhaRect(this->larguraArticulacao, this->alturaArticulacao * 1.05, 1, 0, 0);
}

void Character::DesenhaCanela(int id) {
    if (id == 1) {
        glRotatef(this->gThetaJoelho1, 0, 0, 1);
    } else if (id == 2) {
        glRotatef(this->gThetaJoelho2, 0, 0, 1);
    }

    DesenhaRect(0.4 * this->raioCabeca, this->alturaArticulacao, 1, 0, 0);
}

void Character::DesenhaPerna(int id) {
    glPushMatrix();
    DesenhaCoxa(id);
    glTranslatef(0, this->alturaArticulacao, 0);
    DesenhaCanela(id);
    glPopMatrix();
}

void Character::Anda(GLfloat dx, GLdouble deltaT, bool isPlayer) {
    this->gX += dx * deltaT;

    if (isPlayer) glTranslatef(-dx * deltaT, 0, 0);
}

void Character::Desenha() {
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);
    DesenhaCirc(this->raioCabeca, 0, 1, 0);
    this->DesenhaTronco();
    glTranslatef(0, this->alturaQuadril, 0);
    glRotatef(-90, 0, 0, 1);
    this->DesenhaPerna(1);
    this->DesenhaPerna(2);
    glPopMatrix();
}

GLfloat Character::getCentroCamera() {
    return this->gX;
}