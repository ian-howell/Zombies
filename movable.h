#ifndef MOVABLE_H
#define MOVABLE_H

#include <allegro.h>

class Movable
{
    public:
        Movable(int x, int y, BITMAP* sprite);

        double getx() { return x; }
        double gety() { return y; }

        bool overlaps(const Movable& other, int tol = 0);

        virtual void move(int to_x = 0, int to_y = 0) = 0;
        virtual void draw(BITMAP* buffer);

    protected:
        double speed;

        int x;
        int y;

        int top;
        int bottom;
        int left;
        int right;

        double theta;

        BITMAP* sprite;
};
#endif
