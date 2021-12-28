#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "player.h"
#include "ConfiguracoesJogo.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.01

//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

Player player(0.5, -0.1, 0.3);

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
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
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
 
     player.Desenha();
     
     //if (tiro) tiro->Desenha();
     
     //alvo.Desenha();

     //ImprimePlacar(-230, -230);

     glutSwapBuffers(); // Desenha the new frame of the game.
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-1,     // X coordinate of left edge             
            1,     // X coordinate of right edge            
            0,     // Y coordinate of bottom edge             
            1,     // Y coordinate of top edge             
            -1,     // Z coordinate of the “near” plane            
            1);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}

void idle(void)
{
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;

    // primeira é útil

    double inc = INC_KEYIDLE;
    //Treat keyPress
    if(keyStatus[(int)('a')])
    {
        printf("esquerda\n");
        // player.MoveEmX(-inc);
    }
    if(keyStatus[(int)('d')])
    {
        printf("direita\n");
        // player.MoveEmX(inc);
    }
    
    // //Trata o tiro (soh permite um tiro por vez)
    // //Poderia usar uma lista para tratar varios tiros
    // if(tiro){
    //     tiro->Move(timeDiference);

    //     //Trata colisao
    //     if (alvo.Atingido(tiro)){
    //         alvo.Recria(rand()%500 - 250, 200);
    //         atingido++;
    //     }

    //     if (!tiro->Valido()){ 
    //         delete tiro;
    //         tiro = NULL;
    //     }
    // }
    
    
    // //Control animation
    // if (animate){
    //     static int dir = 1;
    //     if (robo.ObtemX() > (ViewingWidth/2)){
    //         dir *= -1;
    //     }
    //     else if (robo.ObtemX() < -(ViewingWidth/2)){
    //         dir *= -1;
    //     }
    //     robo.MoveEmX(dir*INC_KEYIDLE);
    // }
    
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    ConfiguracoesJogo config("arena_teste.svg");

    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // // Create the window.
    // glutInitWindowSize(Width, Height);
    // glutInitWindowPosition(150,50);
    // glutCreateWindow("Trabalho 2D");
 
    // // Define callbacks.
    // glutDisplayFunc(renderScene);
    // glutKeyboardFunc(keyPress);
    // glutIdleFunc(idle);
    // glutKeyboardUpFunc(keyup);
    
    // init();
 
    // glutMainLoop();
 
    return 0;
}