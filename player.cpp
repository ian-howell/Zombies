#include "player.h"
#include "constants.h"
#include "bitmaps.h"

#include <cmath>

Player::Player(int x, int y) : Movable(x, y, player_sprite)
{
    bottom = top + sprite->h;
    right = left + sprite->w;

    dx = 2;
    dy = 2;
}

void Player::move()
{
    // Motion
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

    // Rotation
    double y = ((top + bottom) / 2.0);
    double x = ((left + right) / 2.0);
    double raw_theta = atan2(mouse_y - y, mouse_x - x);

    theta = ftofix(raw_theta * 128 / M_PI);
}
