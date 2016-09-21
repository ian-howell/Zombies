#ifndef BULLET_H
#define BULLET_H

#include "movable.h"

class Bullet : public Movable
{
    public:
        Bullet(int x, int y);
        Bullet(int x, int y, double raw_theta);
        void move(int to_x = 0, int to_y = 0);

    private:
};
#endif
