#include "utils.h"
#include <math.h>
#define PI 3.14159264

void DesenhaRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f (R, G, B);
    glBegin(GL_QUADS);
        glVertex2f(-width/2, 0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
        glVertex2f(-width/2, height);
    glEnd();
}

void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glPointSize(4);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 5) {
        glVertex2f(
            radius * cos(i * PI / 180),
            radius * sin(i * PI / 180)
        );
    }
    glEnd();
}