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
