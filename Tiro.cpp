#include "Tiro.h"
#include "utils.h"
#include <math.h>

#define PI 3.14159264

#include <iostream>

using namespace std;

Tiro::Tiro(GLfloat x, GLfloat y, GLfloat angulo, GLfloat larguraBraco, GLfloat alturaBraco, GLfloat velocidadeTiro){
    this->gXInit = x;
    this->gX = x;
    this->gYInit = y;
    this->gY = y;
    this->alturaBraco = alturaBraco;
    this->gVel = velocidadeTiro;
    this->gAngulo = angulo;
    this->raioTiro = larguraBraco;
}

void Tiro::DesenhaTiro()
{
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);
    glRotatef(this->gAngulo, 0, 0, 1);
    glTranslatef(this->alturaBraco, 0, 0);
    DesenhaCirc(this->raioTiro, 0.5, 0.5, 1);
    glPopMatrix();
}

void Tiro::Move(GLfloat deltaT) {
    glPushMatrix();
    glRotatef(gAngulo, 0, 0, 1);
    this->gX += deltaT * gVel * cos(gAngulo * PI / 180);
    this->gY += deltaT * gVel * sin(gAngulo * PI / 180);
    glTranslatef(gX, gY, 0);
    glPopMatrix();
}
