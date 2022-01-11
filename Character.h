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
    GLfloat larguraColisao;
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
        bool ColisaoXObstacle(Obstacle o, GLfloat dx, GLdouble deltaT);
        bool ColisaoYObstacle(Obstacle o, GLfloat dy, GLdouble deltaT);
        bool ColisaoXCharacter(Character* c, GLfloat dx, GLdouble deltaT);
        bool ColisaoYCharacter(Character* c, GLfloat dy, GLdouble deltaT);

    public:
        Character(){};
        Character(Circle c, Rect arena, float larguraTotal);
        GLfloat getYPe();
        GLfloat getDirecao();
        void alteraDirecao();
        void Desenha();
        void Anda(GLfloat dx, GLdouble deltaT, bool isPlayer, char direcao);
        void ParaDeAndar();
        bool ColisaoObstacle(Obstacle o, GLfloat dx, GLfloat dy, GLdouble deltaT);
        GLfloat getCentroCamera();
        void Pula(GLfloat deltaT);
        void Cai(GLfloat deltaT);
        bool ColisaoChao(Obstacle o, GLdouble deltaT);
        bool ColisaoCabeca(Character* c, GLdouble deltaT);
        bool ColisaoTeto(Obstacle o, GLdouble deltaT);
        void EstadoInicialY();
        bool getPlayerCaindo();
        void MoveBraco(GLfloat x, GLfloat y);
        Tiro* CriaTiro(GLdouble velocidadeTiro);
        bool ColisaoTiro(Tiro* t);
        bool ColisaoCharacter(Character* c, GLfloat dx, GLfloat dy, GLdouble deltaT);
};

#endif /* CHARACTER_H */