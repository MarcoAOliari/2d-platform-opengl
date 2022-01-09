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
#include "Tiro.h"

using std::vector;

class ConfiguracoesJogo {
    Character player;
    vector<Character> inimigos;
    vector<Obstacle> obstaculos;
    vector<Tiro*> tiros;
    GLfloat limiteArena;

    private:
        bool ColisaoPlayer(Character c, GLfloat dx, GLfloat dy);
        bool ColisaoCabeca(Character c, GLfloat dy, GLdouble deltaT);
        bool ColisaoChao(Character c, GLfloat dy, GLdouble deltaT);
        bool ColisaoTeto(Character c, GLfloat dy, GLdouble deltaT);
        bool ColisaoTiro(Tiro* t);

    public:
        ConfiguracoesJogo(const char *pFilename);
        void Desenha();
        void AndaPlayer(GLfloat dx, GLdouble deltaT, char direcao);
        void ParaDeAndarPlayer();
        GLfloat getCentroCamera();
        void PulaPlayer(GLfloat dy, GLdouble deltaT);
        void CaiPlayer(GLfloat dy, GLdouble deltaT);
        void AtiraPlayer(GLfloat velocidadeTiro, GLdouble deltaT);
        void MoveTiros(GLdouble deltaT);
        void MoveBracoPlayer(GLfloat x, GLfloat y);
};

#endif /* CONFIGURACOES_JOGO_H */