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

ConfiguracoesJogo config;

bool jumping = false;
bool atirou = false;

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
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
}

void ResetKeyStatus()
{
    int i;

    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void renderScene(void)
{
     // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
      
    config.Desenha();

    if (config.FimDeJogo()) {
        config.DesenhaFimDeJogo();
    }

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Black, no opacity(alpha).

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
        config.PulaPlayer(timeDiference);
    } else {
        config.CaiPlayer(timeDiference);
    }

    if (atirou) {
        config.AtiraPlayer(2 * INC_KEY, timeDiference);
        atirou = false;
    } 
    
    config.MoveTiros(timeDiference);

    config.MoveInimigos(timeDiference, INC_KEY);

    config.AtiraInimigos(2 * INC_KEY, timeDiference);
    
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

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "FORNEÇA UM ARQUIVO DE ENTRADA\n";
        exit(EXIT_SUCCESS);
    }

    config.CriaJogo(argv[1]);

    config.PlataformaInimigos(INC_KEY);

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