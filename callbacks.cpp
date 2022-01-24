#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

#include "ConfiguracoesJogo.h"
#include "callbacks.h"

#define FPS 60.0

int keyStatus[256];

const GLint Width = 500;
const GLint Height = 500;

bool jumping = false;
bool atirou = false;

bool inimigosAtiram = true;
bool mudouInimigosAtiram = false;

bool inimigosAndam = true;
bool mudouInimigosAndam = false;

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            keyStatus[(int)('a')] = 1;
            break;
        case 'd':
        case 'D':
            keyStatus[(int)('d')] = 1;
            break;
        case 'r':
        case 'R':
            keyStatus[(int)('r')] = 1;
            break;
        // inimigos não atiram
        case 'i':
        case 'I':
            if (!mudouInimigosAtiram) {
                keyStatus[(int)('i')] = 1;
                mudouInimigosAtiram = true;
                inimigosAtiram = !inimigosAtiram;
            }
            break;
        // inimigos não andam
        case 'o':
        case 'O':
            if (!mudouInimigosAndam) {
                keyStatus[(int)('o')] = 1;
                mudouInimigosAndam = true;
                inimigosAndam = !inimigosAndam;
            }
            break;
        case 27 :
             exit(0);
    }
}

void keyup(unsigned char key, int x, int y) {
    switch (key) {
    case 'i':
    case 'I':
        mudouInimigosAtiram = false;
        keyStatus[(int)(key)] = 0;
        break;
    case 'o':
    case 'O':
        mudouInimigosAndam = false;
        keyStatus[(int)(key)] = 0;
        break;
    default:
        keyStatus[(int)(key)] = 0;
        break;
    }
    
}

void ResetKeyStatus() {
    int i;

    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
      
    config.Desenha();

    if (config.FimDeJogo()) {
        config.DesenhaFimDeJogo();
    }

    glutSwapBuffers();
}

void init(void) {
    ResetKeyStatus();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLfloat centro = config.getCentroCamera();
 
    glMatrixMode(GL_PROJECTION);    
    glOrtho(centro - Width/2,                
            centro + Width/2,            
            500,                
            0,             
            -1,               
            1);    
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity();
      
}

void idle(int value) {
// void idle(void) {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    if (!config.FimDeJogo()) {
        if (keyStatus[(int)('a')] or keyStatus[(int)('d')]) {
            if (keyStatus[(int)('a')]) {
                config.AndaPlayer(-1, timeDiference, 'e');
            }

            if (keyStatus[(int)('d')]) {
                config.AndaPlayer(1, timeDiference, 'd');
            }
        } else {
            config.ParaDeAndarPlayer();
        }

        if (jumping) {
            config.PulaPlayer(timeDiference);
        } else {
            config.CaiPlayer(timeDiference);
        }

        if (atirou) {
            config.AtiraPlayer();
            atirou = false;
        } 

        config.VerificaGanhou(timeDiference);

        if (inimigosAtiram) {
            config.AtiraInimigos(timeDiference);
        }

        config.MoveTiros(timeDiference);

        if (inimigosAndam) {
            config.MoveInimigos(timeDiference);
        }

    } else {
        if (keyStatus[(int)('r')]) {
            config.Restart();
        }
    }
    
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
}