#include "Tiro.h"
#include "utils.h"
#include <math.h>

#define PI 3.14159264

#include <iostream>

using namespace std;

Tiro::Tiro(GLfloat x, GLfloat y, GLfloat angulo, GLfloat larguraBraco, GLfloat alturaBraco, GLfloat velocidadeTiro, char direcao){
    this->gXInit = x;
    this->gX = x;
    this->gYInit = y;
    this->gY = y;
    this->alturaBraco = alturaBraco;
    this->gVel = velocidadeTiro;
    this->gAngulo = angulo;
    this->raioTiro = larguraBraco;
    this->direcao = direcao;
}

GLfloat Tiro::getX() {
    return this->gX;
}

GLfloat Tiro::getY() {
    return this->gY;
}

GLfloat Tiro::getXInit() {
    return this->gXInit;
}

GLfloat Tiro::getYInit() {
    return this->gYInit;
}

GLfloat Tiro::getRaioTiro() {
    return this->raioTiro;
}

GLfloat Tiro::getDx() {
    if (this->direcao == 'd') return gVel * cos(gAngulo * PI / 180);
    else return -gVel * cos(gAngulo * PI / 180);
}

GLfloat Tiro::getDy() {
    return gVel * sin(gAngulo * PI / 180);
}

void Tiro::DesenhaTiro()
{
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);

    if (direcao == 'e') {
        glScalef(-1, 1, 1);
    }

    glRotatef(this->gAngulo, 0, 0, 1);
    glTranslatef(this->alturaBraco, 0, 0);
    DesenhaCirc(this->raioTiro, 0.5, 0.5, 1);
    glPopMatrix();
}

void Tiro::Move(GLfloat deltaT) {
    glPushMatrix();
    glRotatef(gAngulo, 0, 0, 1);

    if (direcao == 'e') {
        this->gX -= deltaT * gVel * cos(gAngulo * PI / 180);
    } else if (direcao == 'd') {
        this->gX += deltaT * gVel * cos(gAngulo * PI / 180);
    }

    this->gY += deltaT * gVel * sin(gAngulo * PI / 180);
    glTranslatef(gX, gY, 0);
    glPopMatrix();
}

bool Tiro::Valido(GLfloat limiteArena) {
    return this->gX < limiteArena + 250 && this->gX > -250 && this->gY < 500 && this->gY > 0;
}

bool Tiro::ColisaoX(Obstacle o, GLfloat dx) {
    if (this->gX + this->raioTiro * 2 + dx > o.getgX() - o.getWidth()/2.0 &&
        this->gX + dx - this->raioTiro * 2 < o.getgX() + o.getWidth()/2.0)
        return true;
    else
        return false;
}

bool Tiro::ColisaoY(Obstacle o, GLfloat dy) {
    if (this->gY + dy + this->raioTiro > o.getgY() &&
        this->gY - this->raioTiro < o.getgY() + o.getHeight())
        return true;
    else
        return false;
}

bool Tiro::ColisaoObstaculo(Obstacle o) {
    if (this->direcao == 'e') {
        return ColisaoX(o, -gVel * cos(gAngulo * PI / 180)) && ColisaoY(o, gVel * sin(gAngulo * PI / 180));
    } else {
        return ColisaoX(o, gVel * cos(gAngulo * PI / 180)) && ColisaoY(o, gVel * sin(gAngulo * PI / 180));
    }
}