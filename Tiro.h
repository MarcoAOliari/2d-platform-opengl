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

    public:
        Tiro(GLfloat x, GLfloat y, GLfloat angulo, GLfloat larguraBraco, GLfloat alturaBraco, GLfloat velocidadeTiro);
        void DesenhaTiro();
        void Move(GLfloat deltaT);
};

#endif /* TIRO_H */