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

    private:
        bool Colisao(Character c, GLfloat dx, GLfloat dy);
        bool ColisaoChao(Character c, GLfloat dy, GLdouble deltaT);
        bool ColisaoTeto(Character c, GLfloat dy, GLdouble deltaT);

    public:
        ConfiguracoesJogo(const char *pFilename);
        void Desenha();
        void AndaPlayer(GLfloat dx, GLdouble deltaT, char direcao);
        void ParaDeAndarPlayer();
        GLfloat getCentroCamera();
        void PulaPlayer(GLfloat dy, GLdouble deltaT);
        void CaiPlayer(GLfloat dy, GLfloat deltaT);
        void MoveBracoPlayer(GLfloat x, GLfloat y);
};

#endif /* CONFIGURACOES_JOGO_H */