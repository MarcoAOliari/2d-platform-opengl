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

void ConfiguracoesJogo::AndaPlayer(GLfloat dx, GLdouble deltaT, char direcao) {
    this->player.Anda(dx, deltaT, true, direcao);
}

void ConfiguracoesJogo::ParaDeAndarPlayer() {
    this->player.ParaDeAndar();
}

GLfloat ConfiguracoesJogo::getCentroCamera() {
    return this->player.getCentroCamera();
}