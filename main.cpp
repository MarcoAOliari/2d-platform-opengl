#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "ConfiguracoesJogo.h"

#define INC_KEY 0.08
#define INC_KEYIDLE 0.01
#define FPS 60.0

int keyStatus[256];

const GLint Width = 500;
const GLint Height = 500;

ConfiguracoesJogo config("arena_teste.svg");

bool jumping = false;
bool atirou = false;
int jumpCounter = 0;

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    //glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    //glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void renderScene(void)
{
     // Clear the screen.
     glClear(GL_COLOR_BUFFER_BIT);
      
    config.Desenha();

     //if (tiro) tiro->Desenha();
     
     //alvo.Desenha();

     //ImprimePlacar(-230, -230);

     glutSwapBuffers(); // Desenha the new frame of the game.
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Black, no opacity(alpha).

    GLfloat centro = config.getCentroCamera();
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(centro - Width/2,     // X coordinate of left edge             
            centro + Width/2,     // X coordinate of right edge            
            500,     // Y coordinate of bottom edge             
            0,     // Y coordinate of top edge             
            -1,     // Z coordinate of the “near” plane            
            1);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}

void idle(int value)
{
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    double inc = INC_KEYIDLE;

    if (keyStatus[(int)('a')] or keyStatus[(int)('d')]) {
        if (keyStatus[(int)('a')]) {
            config.AndaPlayer(-INC_KEY, timeDiference, 'e');
        }

        if (keyStatus[(int)('d')]) {
            config.AndaPlayer(INC_KEY, timeDiference, 'd');
        }
    } else {
        config.ParaDeAndarPlayer();
    }

    if (jumping) {
        config.PulaPlayer(INC_KEY, timeDiference);
    } else {
        config.CaiPlayer(INC_KEY, timeDiference);
    }

    if (atirou) {
        config.AtiraPlayer(2 * INC_KEY, timeDiference);
        atirou = false;
    } 
    
    config.MoveTiros(timeDiference);

    config.MoveInimigos(timeDiference, INC_KEY);
    
    glutPostRedisplay();

    glutTimerFunc(1000.0/FPS, idle, 0);
}

void mouse (int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) jumping = true;
    else jumping = false;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !atirou) atirou = true;
}

void motion (int x, int y) {
    config.MoveBracoPlayer(x, y);
    //glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    config.PlataformaInimigos(INC_KEY);
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Trabalho 2D");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    // glutIdleFunc(idle);
    glutTimerFunc(1000.0/FPS, idle, 0);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    
    init();
 
    glutMainLoop();
 
    return 0;
}