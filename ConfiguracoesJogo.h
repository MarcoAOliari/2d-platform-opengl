#ifndef CONFIGURACOES_JOGO_H
#define CONFIGURACOES_JOGO_H

#include <vector>

#include "SVGReader.h"
#include "Circle.h"
#include "Rect.h"

using std::vector;

class ConfiguracoesJogo {
    Circle player;
    vector<Circle> inimigos;
    Rect arena;
    vector<Rect> obstaculos;

    public:
        ConfiguracoesJogo(const char *pFilename);
};

#endif /* CONFIGURACOES_JOGO_H */