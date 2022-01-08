#include "Character.h"
#include "utils.h"
#include <iostream>
#include <math.h>
#define PI 3.14159264

using namespace std;

Character::Character(Circle c, Rect arena, float larguraTotal) {
    this->gX = larguraTotal * (c.cx - arena.x) / arena.width /*+ 100 */;

    float y = 500 * (c.cy - arena.y) / arena.height /* -  100 */;
    float r = 500 * c.r / arena.height /* + 50 */;

    this->gY = y - 0.75 * r;
    this->raioCabeca = 0.25 * r;
    this->alturaTotal = 2 * r;
    this->alturaQuadril = 0.7 * r;
    this->larguraQuadril = 0.7 * raioCabeca;
    this->alturaArticulacao = 0.43333 * r;
    this->larguraArticulacao = 0.4 * raioCabeca;
    this->alturaBraco = 2 * raioCabeca;
    this->larguraBraco = 0.6 * raioCabeca;
    this->gThetaQuadril1 = 60; 
    this->gThetaQuadril2 = 100; 
    this->gThetaJoelho1 = 30;
    this->gThetaJoelho2 = 0;
    this->gThetaBraco = 0;
    this->velocidadePulo = -0.25;
    this->tiro = NULL;
    this->caindo = false;
    this->frameCaminhada = 0;
    this->direcao = 'd';
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

void Character::DesenhaBraco() {
    glPushMatrix();
    glRotatef(this->gThetaBraco, 0, 0, 1);
    DesenhaRectEixo(this->alturaBraco, this->larguraBraco, 1, 1, 0);
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
        this->gThetaQuadril1 = 70; 
        this->gThetaQuadril2 = 97; 
        this->gThetaJoelho1 = 25;
        this->gThetaJoelho2 = 15;
    } else if (this->frameCaminhada < 600) {
        this->gThetaQuadril1 = 80; 
        this->gThetaQuadril2 = 95; 
        this->gThetaJoelho1 = 20;
        this->gThetaJoelho2 = 25;
    }  else if (this->frameCaminhada < 800) {
        this->gThetaQuadril1 = 86; 
        this->gThetaQuadril2 = 80; 
        this->gThetaJoelho1 = 10;
        this->gThetaJoelho2 = 45;
    } else if (this->frameCaminhada < 1000) {
        this->gThetaQuadril1 = 92; 
        this->gThetaQuadril2 = 70; 
        this->gThetaJoelho1 = 5;
        this->gThetaJoelho2 = 70;
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
    glTranslatef(0, this->alturaQuadril/2.0, 0);
    this->DesenhaBraco();
    glTranslatef(0, this->alturaQuadril/2.0, 0);
    glRotatef(-90, 0, 0, 1);
    this->DesenhaPerna(1);
    this->DesenhaPerna(2);
    glPopMatrix();

    if (this->tiro) {
        this->tiro->DesenhaTiro();
    }
}

GLfloat Character::getCentroCamera() {
    return this->gX;
}

bool Character::ColisaoY(Obstacle o, GLfloat dy) {
    if (this->gY + dy + (this->alturaTotal - this->raioCabeca) > o.getgY() &&
        this->gY - this->raioCabeca < o.getgY() + o.getHeight())
        return true;
    else
        return false;
}

bool Character::ColisaoX(Obstacle o, GLfloat dx) {
    if (this->gX + dx + this->raioCabeca * 2 > o.getgX() - o.getWidth()/2.0 &&
        this->gX + dx - this->raioCabeca * 2 < o.getgX() + o.getWidth()/2.0)
        return true;
    else
        return false;
}

bool Character::ColisaoObstaculo(Obstacle o, GLfloat dx, GLfloat dy) {
    return this->ColisaoX(o, dx) && this->ColisaoY(o, dy);
}

void Character::Pula(GLfloat dy, GLfloat deltaT) {
    if (this->gY + (this->alturaTotal - this->raioCabeca) + this->velocidadePulo * deltaT < 500) {
        this->gY += this->velocidadePulo * deltaT;
        this->velocidadePulo += 0.00015 * deltaT;

        if (this->velocidadePulo >= 0) this->caindo = true;
    }
}

bool Character::ColisaoChao(Obstacle o, GLfloat dy, GLdouble deltaT) {
    if (this->gY + (this->alturaTotal - this->raioCabeca) + 5 * dy * deltaT > o.getgY() && 
        this->gY + (this->alturaTotal - this->raioCabeca) < o.getgY() &&
        this->ColisaoX(o, 0)) {
        return true;
    } else {
        return false;
    }
}

bool Character::ColisaoTeto(Obstacle o, GLfloat dy) {
    if (this->gY - this->raioCabeca + dy < o.getgY() + o.getHeight() &&
        this->gY + (this->alturaTotal - this->raioCabeca) > o.getgY() + o.getHeight() &&
        this->ColisaoX(o, 0)) {
        return true;
    } else {
        return false;
    }
}

void Character::EstadoInicialY() {
    this->caindo = false;
    this->velocidadePulo = -0.25;
}

void Character::Cai(GLfloat dy, GLfloat deltaT) {
    if (this->gY + (this->alturaTotal - this->raioCabeca) - this->velocidadePulo * deltaT < 500) {
        if (this->caindo) {
            this->gY += this->velocidadePulo * deltaT;
            this->velocidadePulo += 0.00015 * deltaT;
        } else {
            this->caindo = true;
            if (this->velocidadePulo < 0) {
                this->velocidadePulo = 0;
            }
        }
    } else {
        this->caindo = false;
        this->velocidadePulo = -0.25;
    }
}

bool Character::getPlayerCaindo() {
    return this->caindo;
}

void Character::MoveBraco(GLfloat x, GLfloat y) {
    GLfloat novoAngulo;
    GLfloat gYBraco = this->gY + this->raioCabeca + this->alturaQuadril/2.0;
    
    if (this->direcao == 'd') {
        novoAngulo = atan((y - gYBraco)/(x - 250)) * 180 / PI;
    } else {
        novoAngulo = -atan((y - gYBraco)/(x - 250)) * 180 / PI;
    }

    if ((novoAngulo > 45 || novoAngulo < -45) && y <= gYBraco) {
        this->gThetaBraco = -45;
    } else if ((novoAngulo > 45 || novoAngulo < -45) && y > gYBraco) {
        this->gThetaBraco = 45;
    } else {
        this->gThetaBraco = novoAngulo;
    }
}

Tiro* Character::CriaTiro(GLdouble velocidadeTiro) {
    return new Tiro(this->gX, this->gY + this->raioCabeca + this->alturaQuadril/2.0, this->gThetaBraco, this->larguraBraco, this->alturaBraco, velocidadeTiro, this->direcao);
}

bool Character::ColisaoTiro(Tiro* t) {
    if (!(this->gX + this->alturaBraco >= t->getXInit() && this->gX - this->alturaBraco <= t->getXInit() &&
        this->gY - this->raioCabeca < t->getYInit() && this->gY + (this->alturaTotal - this->raioCabeca) > t->getYInit())) {

        if (t->getX() + t->getRaioTiro() + t->getDx() > this->gX - this->alturaBraco &&
            t->getX() - t->getRaioTiro() + t->getDx() < this->gX + this->alturaBraco &&
            t->getY() + t->getRaioTiro() + t->getDy() > this->gY - this->raioCabeca &&
            t->getY() - t->getRaioTiro() + t->getDy() < this->gY + (this->alturaTotal - this->raioCabeca)) {
            
            return true;

            // cout << (this->gX + this->alturaBraco <= t->getXInit()) << " " << (this->gX - this->alturaBraco >= t->getXInit()) << " "
            // << (this->gY - this->raioCabeca < t->getYInit()) << " " << (this->gY + (this->alturaTotal - this->raioCabeca) > t->getYInit()) << " " 
            // << t->getXInit() << " " << this->gX << "\n";
        }

    }

    return false;
}