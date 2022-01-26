#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "Circle.h"
#include "Rect.h"
#include "Obstacle.h"
#include "Tiro.h"

// Classe para os personagens do player e todos os inimigos
class Character {
    GLfloat gX;                     // Centro horizontal do personagem
    GLfloat gY;                     // Centro da cabeça do personagem
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
    GLfloat velocidadePulo;         // Velocidade do pulo
    GLfloat aceleracaoPulo;         // Aceleração com que a velocidade do pulo é variada
    GLfloat larguraColisao;         // Limite de colisão horizontal entre personagens e obstáculos ou outros personagens
    bool caindo;
    int tempoCaminhada;             // Utilizado para animar a caminhada do personagem
    char direcao;                   // Direção em que o personagem se movimenta

    private:
        // Desenhos de personagem
        void DesenhaTronco();
        void DesenhaCoxa(int id);
        void DesenhaPerna(int id);
        void DesenhaCanela(int id);
        void DesenhaBraco();

        // "Reinicia" as configurações do personagem para quando está andando
        void PoseParado();

        // Funções de colisão
        bool ColisaoXObstacle(Obstacle o, GLfloat dx, GLdouble deltaT);
        bool ColisaoYObstacle(Obstacle o, GLfloat dy, GLdouble deltaT);
        bool ColisaoXCharacter(Character* c, GLfloat dx, GLdouble deltaT);
        bool ColisaoYCharacter(Character* c, GLfloat dy, GLdouble deltaT);

    public:
        Character(){};
        Character(Circle c, Rect arena, float larguraTotal);

        // Retorna a coordenada y do pé do personagem
        GLfloat getYPe();

        // Retorna a direção em que o personagem está se movimentando
        GLfloat getDirecao();

        // Retorno de coordenadas
        GLfloat getgX();
        GLfloat getgY();

        // Retorno de limites de colisão
        GLfloat getLarguraColisao();

        // Altera coordenadas do inimigo para ajustes em colisões
        void setgYInimigo(Obstacle o);
        void setgXInimigo(GLfloat dx, GLdouble deltaT);

        // Altera a direção de um personagem
        void AlteraDirecao();

        // Desenha personagem por completo
        void Desenha();

        // Movimenta horizontalmente um personagem
        void Anda(GLfloat dx, GLdouble deltaT, bool isPlayer, char direcao);

        // Reinicia movimento de caminhada
        void ParaDeAndar();

        // Verifica colisão com obstáculo
        bool ColisaoObstacle(Obstacle o, GLfloat dx, GLfloat dy, GLdouble deltaT);

        // Verifica colisão com plataforma
        bool ColisaoPlataforma(Obstacle o, GLfloat dx, GLdouble deltaT);

        // Retorna centro da câmera para fixar no personagem
        GLfloat getCentroCamera();

        // Movimenta verticalmente para cima um personagem
        void Pula(GLfloat deltaT);

        // Movimenta verticalmente para baixo um personagem
        void Cai(GLfloat deltaT);

        // Verifica colisão com algum chão
        bool ColisaoChao(Obstacle o, GLdouble deltaT);

        // Verifica colisão com cabeças de personagens
        bool ColisaoCabeca(Character* c, GLdouble deltaT);

        // Verifica colisão com tetos
        bool ColisaoTeto(Obstacle o, GLdouble deltaT);

        // Verifica colisão com limites horizontais do mapa
        bool ColisaoMapa(GLfloat larguraMapa, GLfloat dx, GLdouble deltaT);

        // Retorna às configurações iniciais de pulo do personagem
        void EstadoInicialY();

        // Retorna se o personagem está caindo ou não
        bool getPlayerCaindo();

        // Movimenta braço do personagem
        void MoveBraco(GLfloat x, GLfloat y, bool isPlayer);

        // Cria um novo tiro
        Tiro* CriaTiro(GLdouble velocidadeTiro);

        // Verifica colisão com um tiro
        bool ColisaoTiro(Tiro* t);

        // Verifica colisão com outro personagem
        bool ColisaoCharacter(Character* c, GLfloat dx, GLfloat dy, GLdouble deltaT);

        // Cria um tiro caso o inimigo esteja posicionado de frente para o player
        Tiro* TentaAtirar(GLdouble velocidadeTiro, GLfloat x);
};

#endif /* CHARACTER_H */