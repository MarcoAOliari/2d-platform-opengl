#include "ConfiguracoesJogo.h"
#include "SVGReader.h"

#include <iostream>

using namespace std;

ConfiguracoesJogo::ConfiguracoesJogo(const char *pFilename) {
    SVGReader svg(pFilename);

    vector<Circle> circles = svg.getCircles();
    vector<Rect> rects = svg.getRects();

    for (Circle c : circles) {
        if (c.getIsPlayer()) {
            this->player = c;
        } else {
            this->inimigos.push_back(c);
        }
    }

    for (Rect r : rects) {
        if (r.getIsArena()) {
            this->arena = r;
        } else {
            this->obstaculos.push_back(r);
        }
    }
}