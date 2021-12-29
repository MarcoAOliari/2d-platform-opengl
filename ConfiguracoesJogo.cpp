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
        if (c.getIsPlayer()) {
            this->player = c;
        } else {
            this->inimigos.push_back(c);
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
    for (Obstacle o : this->obstaculos) {
        o.Desenha();
    }
}