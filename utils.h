#ifndef UTILS_H
#define UTILS_H
#include <GL/gl.h>
#include <GL/glu.h>

void DesenhaRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);

void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);

GLfloat Distancia(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

#endif /* UTILS_H */