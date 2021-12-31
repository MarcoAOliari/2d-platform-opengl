#ifndef CONFIGURACOES_JOGO_H
#define CONFIGURACOES_JOGO_H

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SVGReader.h"
#include "Circle.h"
#include "Character.h"
#include "Rect.h"
#include "Obstacle.h"

using std::vector;

class ConfiguracoesJogo {
    Character player;
    vector<Character> inimigos;
    vector<Obstacle> obstaculos;

    public:
        ConfiguracoesJogo(const char *pFilename);
        void Desenha();
        void AndaPlayer(GLfloat dx, GLdouble deltaT);
        void ParaDeAndarPlayer();
        GLfloat getCentroCamera();
};

#endif /* CONFIGURACOES_JOGO_H */