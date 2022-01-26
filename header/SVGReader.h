#ifndef SVG_H
#define SVG_H

#include <vector>
#include "Rect.h"
#include "Circle.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using std::vector;

// Classe para leitor de svg
class SVGReader {
    XMLDocument svg;

    public:
        SVGReader(const char* pFilename);
        vector<Circle> getCircles();
        vector<Rect> getRects();
        
};

#endif