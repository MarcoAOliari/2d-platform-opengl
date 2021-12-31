#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Circle.h"
#include "Rect.h"

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
    GLfloat larguraQuadril;
    GLfloat larguraArticulacao;

private:
    void DesenhaTronco();
    void DesenhaCoxa(int id);
    void DesenhaPerna(int id);
    void DesenhaCanela(int id);

public:
    Character(){};
    Character(Circle c, Rect arena, float larguraTotal);
    void Desenha();
    void Anda(GLfloat dx, GLdouble deltaT, bool isPlayer);
    GLfloat getCentroCamera();
};

#endif /* CHARACTER_H */