#ifndef RECT_H
#define RECT_H

class Rect {
    float width;
    float height;
    float x;
    float y;
    bool isArena;

    public:
        Rect(){};
        Rect(float width, float height, float x, float y, bool isArena);
        bool getIsArena();
};

#endif /* RECT_H */