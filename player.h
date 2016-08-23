#ifndef PLAYER_H
#define PLAYER_H

#include "movable.h"

#include <allegro.h>

class Player : public Movable
{
    public:
        Player(int x, int y, int r);
        void move();
        void draw(BITMAP* buffer);

    private:
        int r;
};
#endif
