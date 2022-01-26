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
    GLfloat centroCamera;
    GLfloat limiteArena;
    GLdouble gameTime;
    GLfloat distanciaPercorrida;
    GLfloat dx;
    bool ganhou;
    bool perdeu;
    const char* fileName;

    private:
        bool ColisaoCharacterObstaculo(Character* c, GLfloat dy, GLdouble deltaT, int multiplicador);
        bool ColisaoCharacterCharacter(Character* c, GLfloat dy, GLdouble deltaT, int multiplicador);
        bool ColisaoCabeca(Character* c, GLdouble deltaT);
        bool ColisaoChao(Character* c, GLdouble deltaT);
        bool ColisaoTeto(Character* c, GLdouble deltaT);
        bool ColisaoMapa(Character* c, GLdouble deltaT, int multiplicador);
        bool ColisaoTiro(Tiro* t);
        void CaiInimigo(Character* c);
        void AndaInimigo(Character* c, GLdouble deltaT, Obstacle o);
        void MoveBracoInimigo(Character* c, GLfloat x, GLfloat y);

    public:
        ConfiguracoesJogo(){};
        bool getGanhou();
        bool getPerdeu();
        void CriaJogo(const char *pFilename);
        void PlataformaInimigos();
        void Desenha();
        void AndaPlayer(int multiplicador, GLdouble deltaT, char direcao);
        void ParaDeAndarPlayer();
        GLfloat getCentroCamera();
        void PulaPlayer(GLdouble deltaT);
        void CaiPlayer(GLdouble deltaT);
        void AtiraPlayer();
        void MoveTiros(GLdouble deltaT);
        void MoveBracoPlayer(GLfloat x, GLfloat y);
        void MoveInimigos(GLdouble deltaT);
        void AtiraInimigos(GLdouble deltaT);
        void VerificaGanhou(GLdouble deltaT);
        bool FimDeJogo();
        void DesenhaFimDeJogo();
        void Restart();
};

#endif /* CONFIGURACOES_JOGO_H */