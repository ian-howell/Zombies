#ifndef MOVABLE_H
#define MOVABLE_H

#include <allegro.h>

class Movable
{
    public:
        Movable(int top, int left);
        virtual void move() = 0;
        virtual void draw(BITMAP* buffer);

    protected:
        int dx;
        int dy;

        int top;
        int bottom;
        int left;
        int right;

        BITMAP* sprite;
};
#endif
