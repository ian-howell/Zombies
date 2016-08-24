#include "player.h"
#include "constants.h"
#include "bitmaps.h"

#include <cmath>

Player::Player(int x, int y) : Movable(x, y, player_sprite)
{
    speed = 2;
}

void Player::move()
{
    // Motion
    if (key[KEY_W] && top > speed)
    {
        top -= speed;
        bottom -= speed;
    }

    if (key[KEY_S] && bottom < HEIGHT)
    {
        top += speed;
        bottom += speed;
    }

    if (key[KEY_A] && left > speed)
    {
        left -= speed;
        right -= speed;
    }

    if (key[KEY_D] && right < WIDTH)
    {
        left += speed;
        right += speed;
    }

    // Rotation
    double y = ((top + bottom) / 2.0);
    double x = ((left + right) / 2.0);
    double raw_theta = atan2(mouse_y - y, mouse_x - x);

    theta = ftofix(raw_theta * 128 / M_PI);
}
