#ifndef RECT_H
#define RECT_H

class Rect {
    public:
        float width;
        float height;
        float x;
        float y;
        bool isArena;
        
        Rect(){};
        Rect(float width, float height, float x, float y, bool isArena);
        bool getIsArena();
        float getX();
        float getY();
        float getHeight();
        float getWidth();
};

#endif /* RECT_H */