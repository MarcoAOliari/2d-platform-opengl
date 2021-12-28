#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
    float cx;
    float cy;
    float r;
    bool isPlayer;

    public:
        Circle(float cx, float cy, float r, bool isPlayer);
};

#endif /* CIRCLE_H */