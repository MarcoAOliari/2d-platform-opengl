#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Circle.h"
#include "Rect.h"
#include "Obstacle.h"
#include "Tiro.h"

class Character {
    GLfloat gX;
    GLfloat gY;
    GLfloat alturaTotal;
    GLfloat raioCabeca;
    GLfloat alturaQuadril;
    GLfloat alturaArticulacao;
    GLfloat alturaBraco;
    GLfloat gThetaQuadril1; 
    GLfloat gThetaQuadril2; 
    GLfloat gThetaJoelho1;
    GLfloat gThetaJoelho2;
    GLfloat gThetaBraco;
    GLfloat larguraQuadril;
    GLfloat larguraArticulacao;
    GLfloat larguraBraco;
    GLfloat velocidadePulo;
    Tiro* tiro;
    bool caindo;
    int frameCaminhada;
    char direcao;

private:
    void DesenhaTronco();
    void DesenhaCoxa(int id);
    void DesenhaPerna(int id);
    void DesenhaCanela(int id);
    void DesenhaBraco();
    void PoseParado();
    bool ColisaoX(Obstacle o, GLfloat dx);
    bool ColisaoY(Obstacle o, GLfloat dy);

public:
    Character(){};
    Character(Circle c, Rect arena, float larguraTotal);
    void Desenha();
    void Anda(GLfloat dx, GLdouble deltaT, bool isPlayer, char direcao);
    void ParaDeAndar();
    bool Colisao(Obstacle o, GLfloat dx, GLfloat dy);
    GLfloat getCentroCamera();
    void Pula(GLfloat dy, GLfloat deltaT);
    void Cai(GLfloat dy, GLfloat deltaT);
    bool ColisaoChao(Obstacle o, GLfloat dy, GLdouble deltaT);
    bool ColisaoTeto(Obstacle o, GLfloat dy);
    void EstadoInicialY();
    bool getPlayerCaindo();
    void MoveBraco(GLfloat x, GLfloat y);
    void Atira(GLdouble velocidadeTiro, GLdouble deltaT);
    void MoveTiro(GLdouble deltaT);
};

#endif /* CHARACTER_H */