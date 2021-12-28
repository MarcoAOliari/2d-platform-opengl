#ifndef RECT_H
#define RECT_H

class Rect {
    float width;
    float height;
    float x;
    float y;
    bool isArena;

    public:
        Rect(float width, float height, float x, float y, bool isArena);
};

#endif /* RECT_H */