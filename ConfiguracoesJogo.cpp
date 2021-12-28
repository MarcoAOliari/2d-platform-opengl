#include "ConfiguracoesJogo.h"
#include "SVGReader.h"

ConfiguracoesJogo::ConfiguracoesJogo(const char *pFilename) {
    SVGReader svg(pFilename);
    
    this->inimigos = svg.getCircles();
    this->obstaculos = svg.getRects();
}