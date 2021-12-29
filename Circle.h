#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
    public:
        float cx;
        float cy;
        float r;
        bool isPlayer;

        Circle(){};
        Circle(float cx, float cy, float r, bool isPlayer);
        bool getIsPlayer();
};

#endif /* CIRCLE_H */