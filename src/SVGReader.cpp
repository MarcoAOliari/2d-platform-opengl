#include "../header/SVGReader.h"
#include "../header/tinyxml2.h"

#include <iostream>
#include <string.h>

using namespace std;
using namespace tinyxml2;

SVGReader::SVGReader(const char* pFilename) {
    XMLError err = this->svg.LoadFile(pFilename);
    if (err != XML_SUCCESS) cout << "Insira um arquivo existente";
}

vector<Circle> SVGReader::getCircles() {
    vector<Circle> circles;
    XMLElement* file = this->svg.FirstChildElement();

    for (XMLElement* circle = file->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle")) {
        float cx, cy, r;

        circle->QueryFloatAttribute("cx", &cx);
        circle->QueryFloatAttribute("cy", &cy);
        circle->QueryFloatAttribute("r", &r);

        bool isPlayer = !strcmp(circle->Attribute("fill"),"green");

        Circle c(cx, cy, r, isPlayer);

        circles.push_back(c);
    }

    return circles;
}

vector<Rect> SVGReader::getRects() {
    vector<Rect> rects;
    XMLElement* file = this->svg.FirstChildElement();

    for (XMLElement* rect = file->FirstChildElement("rect"); rect != NULL; rect = rect->NextSiblingElement("rect")) {
        float width, height, x, y;

        rect->QueryFloatAttribute("width", &width);
        rect->QueryFloatAttribute("height", &height);
        rect->QueryFloatAttribute("x", &x);
        rect->QueryFloatAttribute("y", &y);

        bool isArena = !strcmp(rect->Attribute("fill"),"blue");

        Rect newRect(width, height, x, y, isArena);

        rects.push_back(newRect);
    }

    return rects;  
}