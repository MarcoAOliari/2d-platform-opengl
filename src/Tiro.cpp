#include "../header/Tiro.h"
#include "../header/utils.h"
#include <math.h>

#define PI 3.14159264

#include <iostream>

using namespace std;

Tiro::Tiro(GLfloat x, GLfloat y, GLfloat angulo, GLfloat larguraBraco, GLfloat alturaBraco, GLfloat velocidadeTiro, char direcao){
    if (direcao == 'd') {
        this->gXInit = x + alturaBraco * cos(angulo * PI / 180);
        this->gX = x + alturaBraco * cos(angulo * PI / 180);
    } else if (direcao == 'e') {
        this->gXInit = x - alturaBraco * cos(angulo * PI / 180);
        this->gX = x - alturaBraco * cos(angulo * PI / 180);
    }

    this->gYInit = y;
    this->gY = y;
    this->alturaBraco = alturaBraco;
    this->gVel = velocidadeTiro;
    this->gAngulo = angulo;
    this->raioTiro = larguraBraco * 0.6;
    this->direcao = direcao;
}

GLfloat Tiro::getX() {
    if (this->direcao == 'd') {
        return this->gX + this->alturaBraco * cos(this->gAngulo * PI / 180);
    } else {
        return this->gX - this->alturaBraco * cos(this->gAngulo * PI / 180);
    }
}

GLfloat Tiro::getY() {
    return this->gY + this->alturaBraco * sin(this->gAngulo * PI / 180);;
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
    if (this->direcao == 'd') return this->gVel * cos(this->gAngulo * PI / 180);
    else return -this->gVel * cos(this->gAngulo * PI / 180);
}

GLfloat Tiro::getDy() {
    return this->gVel * sin(this->gAngulo * PI / 180);
}

void Tiro::DesenhaTiro()
{
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);

    if (this->direcao == 'e') {
        glScalef(-1, 1, 1);
    }

    glRotatef(this->gAngulo, 0, 0, 1);
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