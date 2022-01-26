#include "../header/ConfiguracoesJogo.h"
#include "../header/SVGReader.h"
#include "../header/utils.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

using namespace std;

static char str[1000];
void * font = GLUT_BITMAP_9_BY_15;

bool ConfiguracoesJogo::getGanhou() {
    return this->ganhou;
}

bool ConfiguracoesJogo::getPerdeu() {
    return this->perdeu;
}

void ConfiguracoesJogo::CriaJogo(const char *pFilename) {
    SVGReader svg(pFilename);

    vector<Circle> circles = svg.getCircles();
    vector<Rect> rects = svg.getRects();

    float larguraTotal;
    Rect arena;

    for (Rect r : rects) {
        if (r.getIsArena()) {
            larguraTotal = r.width * 500 / r.height;
            this->limiteArena = larguraTotal;
            arena = r;
            break;
        }
    }

    for (Circle c : circles) {
        if (c.getIsPlayer()) {
            this->player = new Character(c, arena, larguraTotal);
        } else {
            this->inimigos.push_back(new Character (c, arena, larguraTotal));
        }
    }

    for (Rect r : rects) {
        if (!r.getIsArena()) {
            Obstacle o(r, arena, larguraTotal);
            this->obstaculos.push_back(o);
        }
    }

    Obstacle chao(larguraTotal);
    this->chao = chao;
    this->gameTime = 0;
    this->centroCamera = this->player->getgX();
    this->dx = this->player->getLarguraColisao()/150;
    this->ganhou = false;
    this->perdeu = false;
    this->fileName = pFilename;
    this->distanciaPercorrida = 0;
}

void ConfiguracoesJogo::PlataformaInimigos() {
    for (Character* c : this->inimigos) {
        this->CaiInimigo(c);
    }

    for (int i = 0; i < this->inimigos.size(); i++) {
        inimigos[i]->setgYInimigo(this->plataformaInimigos[i]);
    }
}

void ConfiguracoesJogo::CaiInimigo(Character* c) {
    bool plataforma = false;

    while (!plataforma) {
        for (Obstacle o : this->obstaculos) {
            if (c->ColisaoChao(o, 1)) {
                plataforma = true;
                this->plataformaInimigos.push_back(o);
                break;
            } else if (c->getYPe() >= 500 - this->dx) {
                plataforma = true;
                this->plataformaInimigos.push_back(this->chao);
                break;
            }
        }
        c->Cai(1);
    }

}

void ConfiguracoesJogo::Desenha() {
    glPushMatrix();
    glTranslatef(this->limiteArena/2.0, 0, 0);
    DesenhaRect(this->limiteArena, 500, 0, 0, 1);
    glPopMatrix();

    this->player->Desenha();

    for (Obstacle o : this->obstaculos) {
        o.Desenha();
    }

    for (Character* c : this->inimigos) {
        c->Desenha();
    }

    for (Tiro* t : this->tiros) {
        t->DesenhaTiro();
    }

}

bool ConfiguracoesJogo::ColisaoCharacterObstaculo(Character* c, GLfloat dy, GLdouble deltaT, int multiplicador) {
    for (Obstacle o : this->obstaculos) {
        if (c->ColisaoObstacle(o, multiplicador * this->dx, dy, deltaT)){
            return true;
        }
    }
    return false;
}

bool ConfiguracoesJogo::ColisaoCharacterCharacter(Character* c, GLfloat dy, GLdouble deltaT, int multiplicador) {
    for (Character* c2 : this->inimigos) {
        if (c->ColisaoCharacter(c2, multiplicador * this->dx, dy, deltaT)) {
            return true;
        }
    }

    if (c->ColisaoCharacter(this->player, multiplicador * this->dx, dy, deltaT)) {
        return true;
    }

    return false;
}

bool ConfiguracoesJogo::ColisaoTiro(Tiro* t) {
    for (Obstacle o : this->obstaculos) {
        if (t->ColisaoObstaculo(o)){
            return true;
        }
    }

    vector<Character*>::iterator it;
    int index = 0;

    for (it = this->inimigos.begin(); it != this->inimigos.end();) {
        if ((*it)->ColisaoTiro(t)){
            delete *it;
            it = this->inimigos.erase(it);

            this->plataformaInimigos.erase(this->plataformaInimigos.begin() + index);

            return true;
        } else {
            ++it;
            index++;
        }
    }

    if (this->player->ColisaoTiro(t)) {
        delete this->player;
        this->perdeu = true;
        return true;
    }

    return false;
}

bool ConfiguracoesJogo::ColisaoCabeca(Character* c, GLdouble deltaT) {
    for (Character* c2 : this->inimigos) {
        if(c->ColisaoCabeca(c2, deltaT)) {
            return true;
        }
    }

    if (c->ColisaoCabeca(this->player, deltaT)) {
        return true;
    }

    return false;
}

bool ConfiguracoesJogo::ColisaoChao(Character* c, GLdouble deltaT) {
    for (Obstacle o : this->obstaculos) {
        if (c->ColisaoChao(o, deltaT)){ 
            return true;
        }
    }
    return false;
}

bool ConfiguracoesJogo::ColisaoTeto(Character* c, GLdouble deltaT) {
    for (Obstacle o : this->obstaculos) {
        if (c->ColisaoTeto(o, deltaT)){ 
            return true;
        }
    }
    return false;
}

bool ConfiguracoesJogo::ColisaoMapa(Character* c, GLdouble deltaT, int multiplicador) {
    return c->ColisaoMapa(this->limiteArena, multiplicador * this->dx, deltaT);
}

void ConfiguracoesJogo::AndaPlayer(int multiplicador, GLdouble deltaT, char direcao) {
    if (!this->ColisaoMapa(this->player, deltaT, multiplicador) &&
        !this->ColisaoCharacterObstaculo(this->player, 0, deltaT, multiplicador) &&
        !this->ColisaoCharacterCharacter(this->player, 0, deltaT, multiplicador)) {

        this->player->Anda(multiplicador * this->dx, deltaT, true, direcao);
        this->distanciaPercorrida += multiplicador * this->dx * deltaT;
        this->centroCamera = this->player->getgX();
    }
}

void ConfiguracoesJogo::ParaDeAndarPlayer() {
    this->player->ParaDeAndar();
}

void ConfiguracoesJogo::PulaPlayer(GLdouble deltaT) {
    if (!this->ColisaoTeto(this->player, deltaT) && !this->player->getPlayerCaindo()) {
        this->player->Pula(deltaT);
    } else {
        this->CaiPlayer(deltaT);
    }
}

void ConfiguracoesJogo::CaiPlayer(GLdouble deltaT) {
    if (!this->ColisaoChao(this->player, deltaT) && !this->ColisaoCabeca(this->player, deltaT)) {
        this->player->Cai(deltaT);
    } else {
        this->player->EstadoInicialY();
    }
}

GLfloat ConfiguracoesJogo::getCentroCamera() {
    return this->player->getCentroCamera();
}

void ConfiguracoesJogo::MoveBracoPlayer(GLfloat x, GLfloat y) {
    this->player->MoveBraco(x, y, true);
}

void ConfiguracoesJogo::AtiraPlayer() {
    this->tiros.push_back(this->player->CriaTiro(2 * this->dx));
}

void ConfiguracoesJogo::MoveTiros(GLdouble deltaT) {
    vector<Tiro*>::iterator it;

    for (it = this->tiros.begin(); it != this->tiros.end();) {
        if ((*it)->Valido(this->limiteArena) && !this->ColisaoTiro((*it))){
            (*it)->Move(deltaT);
            ++it;
        } else {
            delete *it;
            it = this->tiros.erase(it);
        }
    }
}

void ConfiguracoesJogo::AndaInimigo(Character* c, GLdouble deltaT, Obstacle o) {
    char dir = c->getDirecao();
    int multiplicador = dir == 'd' ? 1 : -1;

    if (ColisaoCharacterObstaculo(c, 0, deltaT, multiplicador) || ColisaoCharacterCharacter(c, 0, deltaT, multiplicador) || 
        c->ColisaoPlataforma(o, multiplicador * this->dx, deltaT) || c->ColisaoMapa(this->limiteArena, multiplicador * this->dx, deltaT)) {
        c->AlteraDirecao();
        return;
    }

    if (dir == 'd') {
        c->Anda(this->dx, deltaT, false, dir);
    } else if (dir == 'e') {
        c->Anda(-this->dx, deltaT, false, dir);
    }
}

void ConfiguracoesJogo::MoveBracoInimigo(Character* c, GLfloat x, GLfloat y) {
    c->MoveBraco(x, y, false);
}

void ConfiguracoesJogo::MoveInimigos(GLdouble deltaT) {
    for (int i = 0; i < this->inimigos.size(); i++) {
        this->AndaInimigo(this->inimigos[i], deltaT, this->plataformaInimigos[i]);
        this->MoveBracoInimigo(this->inimigos[i], this->player->getgX(), this->player->getgY()); 
    }
}

void ConfiguracoesJogo::AtiraInimigos(GLdouble deltaT) {
    this->gameTime += deltaT;

    if (this->gameTime > 2500) {
        for (Character* c : this->inimigos) {
            Tiro* t = c->TentaAtirar(2 * this->dx, this->player->getgX());

            if (t) {
                this->tiros.push_back(t);
            }
        }
        this->gameTime = 0;
    }
}

void ConfiguracoesJogo::VerificaGanhou(GLdouble deltaT) {
    if (this->player->getgX() + this->player->getLarguraColisao() + this->dx * deltaT > this->limiteArena) {
        this->ganhou = true;
    }
}

bool ConfiguracoesJogo::FimDeJogo() {
    return this->ganhou || this->perdeu;
}

void ConfiguracoesJogo::DesenhaFimDeJogo() {
    glColor3f(1.0, 1.0, 1.0);

    char *tmpStr;

    if (this->ganhou) {
        sprintf(str, "Parabens, voce ganhou!");
        glRasterPos2f(this->centroCamera - 80, 250);
    } else if (this->perdeu) {
        sprintf(str, "Voce perdeu!");
        glRasterPos2f(this->centroCamera - 40, 250);
    }

    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }

    sprintf(str, "Pressione R para reiniciar o jogo");
    glRasterPos2f(this->centroCamera - 130, 270);

    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void ConfiguracoesJogo::Restart() {

    if (!this->perdeu) {
        delete this->player;
    }

    for (Character* c : this->inimigos) {
        delete c;
    }

    for (Tiro* t : this->tiros) {
        delete t;
    }

    this->inimigos.clear();
    this->obstaculos.clear();
    this->tiros.clear();
    this->plataformaInimigos.clear();

    glTranslatef(this->distanciaPercorrida, 0, 0);

    this->CriaJogo(this->fileName);
    this->PlataformaInimigos();
}
