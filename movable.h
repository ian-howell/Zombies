#ifndef MOVABLE_H
#define MOVABLE_H

#include <allegro.h>

class Movable
{
    public:
        Movable(int x, int y);
        virtual void move() = 0;
        virtual void draw(BITMAP* buffer) = 0;

    protected:
        int x;
        int y;

        int dx;
        int dy;
};
#endif
