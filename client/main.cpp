#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "../header/ConfiguracoesJogo.h"
#include "../header/callbacks.h"

#define FPS 60.0

const GLint Width = 500;
const GLint Height = 500;

ConfiguracoesJogo config;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "FORNEÇA UM ARQUIVO DE ENTRADA\n";
        exit(EXIT_SUCCESS);
    }

    config.CriaJogo(argv[1]);

    config.PlataformaInimigos();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Cria a janela
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Trabalho 2D");
 
    // Definição dos callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutTimerFunc(1000.0/FPS, idle, 0);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    
    init();
 
    glutMainLoop();
 
    return 0;
}