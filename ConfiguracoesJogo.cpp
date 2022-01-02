#include "ConfiguracoesJogo.h"
#include "SVGReader.h"

#include <iostream>

using namespace std;

ConfiguracoesJogo::ConfiguracoesJogo(const char *pFilename) {
    SVGReader svg(pFilename);

    vector<Circle> circles = svg.getCircles();
    vector<Rect> rects = svg.getRects();

    float larguraTotal, arenaX, arenaY, larguraArena;
    Rect arena;

    for (Rect r : rects) {
        if (r.getIsArena()) {
            larguraTotal = r.width * 500 / r.height;
            arena = r;
            break;
        }
    }

    for (Circle c : circles) {
        Character ch(c, arena, larguraTotal);
        if (c.getIsPlayer()) {
            this->player = ch;
        } else {
            this->inimigos.push_back(ch);
        }
    }

    for (Rect r : rects) {
        if (!r.getIsArena()) {
            Obstacle o(r, arena, larguraTotal);
            this->obstaculos.push_back(o);
        }
    }
}

void ConfiguracoesJogo::Desenha() {
    this->player.Desenha();

    for (Obstacle o : this->obstaculos) {
        o.Desenha();
    }

    for (Character c : this->inimigos) {
        c.Desenha();
    }
}

bool ConfiguracoesJogo::Colisao(Character c, GLfloat dx, GLfloat dy) {
    for (Obstacle o : this->obstaculos) {
        if (c.Colisao(o, dx, dy)){ 
            return true;
        }
    }
    return false;
}

bool ConfiguracoesJogo::ColisaoChao(Character c, GLfloat dy, GLdouble deltaT) {
    for (Obstacle o : this->obstaculos) {
        if (c.ColisaoChao(o, dy)){ 
            return true;
            cout << "COLIDIU!\n";
        }
    }
    return false;
}

void ConfiguracoesJogo::AndaPlayer(GLfloat dx, GLdouble deltaT, char direcao) {
    if (!this->Colisao(this->player, dx, 0))
        this->player.Anda(dx, deltaT, true, direcao);
}

void ConfiguracoesJogo::ParaDeAndarPlayer() {
    this->player.ParaDeAndar();
}

void ConfiguracoesJogo::PulaPlayer(GLfloat dy, GLdouble deltaT) {
    this->player.Pula(dy, deltaT);
}

void ConfiguracoesJogo::CaiPlayer(GLfloat dy, GLfloat deltaT) {
    if (!this->ColisaoChao(this->player, dy, deltaT)) {
        this->player.Cai(dy, deltaT);
    } else {
        this->player.EstadoInicialY();
    }
}

GLfloat ConfiguracoesJogo::getCentroCamera() {
    return this->player.getCentroCamera();
}