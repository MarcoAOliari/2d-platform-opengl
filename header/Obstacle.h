#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Rect.h"

// Classe de um obstáculo do jogo
class Obstacle {
    GLfloat gX;
    GLfloat gY;
    GLfloat width;
    GLfloat height;

public:
    Obstacle(Rect r, Rect arena, float larguraTotal);
    Obstacle(float larguraTotal);
    Obstacle(){};

    void Desenha();
    GLfloat getgX();
    GLfloat getgY();
    GLfloat getWidth();
    GLfloat getHeight();
};

#endif /* OBSTACLE_H */