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
    alturaTotal = 2 * r;
    alturaQuadril = 0.7 * r;
    larguraQuadril = 0.7 * raioCabeca;
    alturaArticulacao = 0.43333 * r;
    larguraArticulacao = 0.4 * raioCabeca;
    gThetaQuadril1 = 60; 
    gThetaQuadril2 = 100; 
    gThetaJoelho1 = 30;
    gThetaJoelho2 = 0;
    direcao = 'd';
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

void Character::PoseParado() {
    gThetaQuadril1 = 60; 
    gThetaQuadril2 = 100; 
    gThetaJoelho1 = 30;
    gThetaJoelho2 = 0;
}

void Character::Anda(GLfloat dx, GLdouble deltaT, bool isPlayer, char direcao) {
    this->gX += dx * deltaT;
    this->direcao = direcao;

    this->frameCaminhada = (this->frameCaminhada + 1) % 1000;

    if (this->frameCaminhada < 200) {
        this->PoseParado();

    } else if (this->frameCaminhada < 400){
        gThetaQuadril1 = 70; 
        gThetaQuadril2 = 97; 
        gThetaJoelho1 = 25;
        gThetaJoelho2 = 15;
    } else if (this->frameCaminhada < 600) {
        gThetaQuadril1 = 80; 
        gThetaQuadril2 = 95; 
        gThetaJoelho1 = 20;
        gThetaJoelho2 = 25;
    }  else if (this->frameCaminhada < 800) {
        gThetaQuadril1 = 86; 
        gThetaQuadril2 = 80; 
        gThetaJoelho1 = 10;
        gThetaJoelho2 = 45;
    } else if (this->frameCaminhada < 1000) {
        gThetaQuadril1 = 92; 
        gThetaQuadril2 = 70; 
        gThetaJoelho1 = 5;
        gThetaJoelho2 = 70;
    }

    if (isPlayer) glTranslatef(-dx * deltaT, 0, 0);
}

void Character::ParaDeAndar() {
    this->frameCaminhada = 0;
    this->PoseParado();
}

void Character::Desenha() {
    glPushMatrix();
    glTranslatef(this->gX, this->gY, 0);

    if (this->direcao == 'e') {
        glScalef(-1, 1, 1);
    }

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

bool Character::ColisaoY(Obstacle o, GLfloat dy) {
    if (this->gY + dy + this->raioCabeca < o.getgY() ||
        this->gY + dy - (this->alturaTotal - this->raioCabeca) > o.getgY() + o.getWidth()){
            cout << "Colisao Y!\n";
        return true;}
    else
        return false;
}

bool Character::ColisaoX(Obstacle o, GLfloat dx) {
    if (this->gX + dx + this->raioCabeca * 3.5 > o.getgX() - o.getWidth()/2.0 &&
        this->gX + dx - this->raioCabeca * 3.5 < o.getgX() + o.getWidth()/2.0){
            cout << "Colisao X!\n";
        return true;}
    else
        return false;
}

bool Character::Colisao(Obstacle o, GLfloat dx, GLfloat dy) {
    return this->ColisaoX(o, dx) && this->ColisaoY(o, dy);
}