#ifndef TIRO_H
#define TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

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

    public:
        Tiro(GLfloat x, GLfloat y, GLfloat angulo, GLfloat larguraBraco, GLfloat alturaBraco, GLfloat velocidadeTiro, char direcao);
        void DesenhaTiro();
        void Move(GLfloat deltaT);
        bool Valido(GLfloat limiteArena);
};

#endif /* TIRO_H */