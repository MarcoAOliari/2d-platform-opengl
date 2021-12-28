#include "Obstacle.h"
#include <iostream>

using namespace std;

Obstacle::Obstacle(Rect r, Rect arena, float larguraTotal) {
    this->gX = larguraTotal * (r.x - arena.x) / arena.width;
    this->gY = 500 * (r.y - arena.y) / arena.height;
    this->height = 500 * r.height / arena.height;
    this->width = larguraTotal * r.width / arena.width;

    // cout << r.x << " " << r.y << " -> " << this->gX << " " << this->gY << "\n";
    // cout << r.width << " " << r.height << " -> " << this->width << " " << this->height << "\n\n";
}