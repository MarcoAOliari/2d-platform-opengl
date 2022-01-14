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
    Character* player;
    vector<Character*> inimigos;
    vector<Obstacle> obstaculos;
    vector<Tiro*> tiros;
    vector<Obstacle> plataformaInimigos;
    Obstacle chao;
    GLfloat limiteArena;
    GLdouble gameTime;

    private:
        bool ColisaoCharacterObstaculo(Character* c, GLfloat dx, GLfloat dy, GLdouble deltaT);
        bool ColisaoCharacterCharacter(Character* c, GLfloat dx, GLfloat dy, GLdouble deltaT);
        bool ColisaoCabeca(Character* c, GLdouble deltaT);
        bool ColisaoChao(Character* c, GLdouble deltaT);
        bool ColisaoTeto(Character* c, GLdouble deltaT);
        bool ColisaoMapa(Character* c, GLfloat dx, GLdouble deltaT);
        bool ColisaoTiro(Tiro* t);
        void CaiInimigo(Character* c, GLfloat dy);
        void AndaInimigo(Character* c, GLfloat dx, GLdouble deltaT, Obstacle o);
        void MoveBracoInimigo(Character* c, GLfloat x, GLfloat y);

    public:
        ConfiguracoesJogo(const char *pFilename);
        void PlataformaInimigos(GLfloat dy);
        void Desenha();
        void AndaPlayer(GLfloat dx, GLdouble deltaT, char direcao);
        void ParaDeAndarPlayer();
        GLfloat getCentroCamera();
        void PulaPlayer(GLdouble deltaT);
        void CaiPlayer(GLdouble deltaT);
        void AtiraPlayer(GLfloat velocidadeTiro, GLdouble deltaT);
        void MoveTiros(GLdouble deltaT);
        void MoveBracoPlayer(GLfloat x, GLfloat y);
        void MoveInimigos(GLdouble deltaT, GLfloat dx);
        void AtiraInimigos(GLfloat velocidadeTiro, GLdouble deltaT);
};

#endif /* CONFIGURACOES_JOGO_H */