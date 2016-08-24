#include "player.h"
#include "constants.h"
#include "bitmaps.h"

Player::Player(int top, int left) : Movable(top, left)
{
    sprite = player_sprite;

    bottom = top + sprite->h;
    right = left + sprite->w;

    dx = 2;
    dy = 2;
}

void Player::move()
{
    if (key[KEY_W] && top > dy)
    {
        top -= dy;
        bottom -= dy;
    }

    if (key[KEY_S] && bottom < HEIGHT)
    {
        top += dy;
        bottom += dy;
    }

    if (key[KEY_A] && left > dx)
    {
        left -= dx;
        right -= dx;
    }

    if (key[KEY_D] && right < WIDTH)
    {
        left += dx;
        right += dx;
    }

}
