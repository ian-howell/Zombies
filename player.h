#ifndef PLAYER_H
#define PLAYER_H

#include "movable.h"

class Player : public Movable
{
    public:
        Player(int x, int y);
        void move(int to_x = 0, int to_y = 0);

    private:
};
#endif
