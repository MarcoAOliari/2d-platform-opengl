#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
    float cx;
    float cy;
    float r;
    bool isPlayer;

    public:
        Circle(){};
        Circle(float cx, float cy, float r, bool isPlayer);
        bool getIsPlayer();
};

#endif /* CIRCLE_H */