#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Rect.h"

class Obstacle {
    GLfloat gX;
    GLfloat gY;
    GLfloat width;
    GLfloat height;

public:
    Obstacle(Rect r, Rect arena, float larguraTotal);

    void Desenha();
};

#endif /* OBSTACLE_H */