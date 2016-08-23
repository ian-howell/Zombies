#ifndef PLAYER_H
#define PLAYER_H

#include <allegro.h>

class Player
{
    public:
        Player();
        void move();
        void draw(BITMAP* buffer);

    private:
        int x;
        int y;
        int r;

        int dx;
        int dy;
};
#endif
