#ifndef UTILS_H
#define UTILS_H
#include <GL/gl.h>
#include <GL/glu.h>

// Funções de desenho básicas
void DesenhaRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);

void DesenhaRectEixo(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);

void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);

// Cálculo da distância euclidiana entre dois pontos
GLfloat Distancia(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

#endif /* UTILS_H */