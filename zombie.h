#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "movable.h"

#include <allegro.h>

class Zombie : public Movable
{
    public:
        Zombie(int x, int y);
        void move(int to_x, int to_y);

    private:
};
#endif
