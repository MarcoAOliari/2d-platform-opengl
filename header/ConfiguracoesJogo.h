#ifndef CONFIGURACOES_JOGO_H
#define CONFIGURACOES_JOGO_H

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SVGReader.h"
#include "Circle.h"
#include "Character.h"
#include "Rect.h"
#include "Obstacle.h"
#include "Tiro.h"

using std::vector;

// Classe geral que contem todo o jogo
class ConfiguracoesJogo {
    Character* player;
    vector<Character*> inimigos;
    vector<Obstacle> obstaculos;
    vector<Tiro*> tiros;
    vector<Obstacle> plataformaInimigos;        // Plataformas em que cada inimigo está se movimentando
    Obstacle chao;
    GLfloat centroCamera;
    GLfloat limiteArena;
    GLdouble gameTime;                          // Tempo de jogo, utilizado para controlar o tempo de tiro dos inimigos
    GLfloat distanciaPercorrida;                // Distância total percorrida pelo personagem, utilizada para reiniciar o jogo e recentralizar a câmera
    GLfloat dx;
    bool ganhou;
    bool perdeu;
    const char* fileName;

    private:
        // Verificação de todas as colisões presentes no jogo
        bool ColisaoCharacterObstaculo(Character* c, GLfloat dy, GLdouble deltaT, int multiplicador);
        bool ColisaoCharacterCharacter(Character* c, GLfloat dy, GLdouble deltaT, int multiplicador);
        bool ColisaoCabeca(Character* c, GLdouble deltaT);
        bool ColisaoChao(Character* c, GLdouble deltaT);
        bool ColisaoTeto(Character* c, GLdouble deltaT);
        bool ColisaoMapa(Character* c, GLdouble deltaT, int multiplicador);
        bool ColisaoTiro(Tiro* t);

        // Função auxiliar para encontrar a plataforma em que um personagem se situa
        void CaiInimigo(Character* c);

        // Movimenta um inimigo conforme as colisões existentes
        void AndaInimigo(Character* c, GLdouble deltaT, Obstacle o);

        // Movimenta o braço do inimigo considerando a posição do player
        void MoveBracoInimigo(Character* c, GLfloat x, GLfloat y);

    public:
        ConfiguracoesJogo(){};

        // Retornam condições de fim de jogo
        bool getGanhou();
        bool getPerdeu();

        // Configura o jogo com a leitura do svg
        void CriaJogo(const char *pFilename);

        // Preenche o vector com a plataforma de cada inimigo
        void PlataformaInimigos();

        // Desenha todos os elementos do jogo
        void Desenha();

        // Movimenta o player conforme as teclas pressionadas
        void AndaPlayer(int multiplicador, GLdouble deltaT, char direcao);

        // Reinicia movimento de caminhada do player
        void ParaDeAndarPlayer();

        // Retorna centro da câmera para centralizar no player
        GLfloat getCentroCamera();

        // Movimentos verticais do player conforme os cliques no mouse
        void PulaPlayer(GLdouble deltaT);
        void CaiPlayer(GLdouble deltaT);

        // Player atira conforma cliques no mouse
        void AtiraPlayer();

        // Movimenta todos os tiros criados por personagens
        void MoveTiros(GLdouble deltaT);

        // Movimenta braço do player conforme posição do mouse
        void MoveBracoPlayer(GLfloat x, GLfloat y);

        // Movimenta inimigos verificando colisões
        void MoveInimigos(GLdouble deltaT);

        // Verifica possibilidade de tiro para todos os inimigos vivos
        void AtiraInimigos(GLdouble deltaT);

        // Funções de fim de jogo
        void VerificaGanhou(GLdouble deltaT);
        bool FimDeJogo();
        void DesenhaFimDeJogo();
        void Restart();
};

#endif /* CONFIGURACOES_JOGO_H */