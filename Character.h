#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Circle.h"

class Character {
    GLfloat gX;
    GLfloat gY;
    GLfloat raioCabeca;
    GLfloat alturaQuadril;
    GLfloat alturaArticulacao;
    GLfloat gThetaQuadril1; 
    GLfloat gThetaQuadril2; 
    GLfloat gThetaJoelho1;
    GLfloat gThetaJoelho2;

private:


public:
    Character(Circle c);

    void Desenha();

};

#endif /* CHARACTER_H */