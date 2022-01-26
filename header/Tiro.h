#ifndef TIRO_H
#define TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Obstacle.h"

// Classe de tiro de todos os personagens
class Tiro {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY;
    GLfloat alturaBraco;
    GLfloat gAngulo;
    GLfloat gVel;
    GLfloat raioTiro;
    char direcao;     

    private:
        bool ColisaoX(Obstacle o, GLfloat dx);
        bool ColisaoY(Obstacle o, GLfloat dy);

    public:
        Tiro(GLfloat x, GLfloat y, GLfloat angulo, GLfloat larguraBraco, GLfloat alturaBraco, GLfloat velocidadeTiro, char direcao);
        GLfloat getX();
        GLfloat getY();
        GLfloat getRaioTiro();

        // Retornam variações futuras do tiro para verificar colisões
        GLfloat getDx();
        GLfloat getDy();

        // Retornam posições iniciais do tiro
        GLfloat getXInit();
        GLfloat getYInit();
        void DesenhaTiro();
        void Move(GLfloat deltaT);

        // Auxilia na remoção dos tiros distantes da arena ou colididos
        bool Valido(GLfloat limiteArena);
        bool ColisaoObstaculo(Obstacle o);
};

#endif /* TIRO_H */