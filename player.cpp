#include "player.h"
#include "constants.h"
#include "bitmaps.h"

#include <cmath>

Player::Player(int x, int y) : Movable(x, y, player_sprite)
{
    speed = 7.0;
}

void Player::move(int to_x, int to_y)
{
    // Motion
    if (key[KEY_W] && top > speed)
    {
        y -= speed;
        top -= speed;
        bottom -= speed;
    }

    if (key[KEY_S] && bottom < HEIGHT)
    {
        y += speed;
        top += speed;
        bottom += speed;
    }

    if (key[KEY_A] && left > speed)
    {
        x -= speed;
        left -= speed;
        right -= speed;
    }

    if (key[KEY_D] && right < WIDTH)
    {
        x += speed;
        left += speed;
        right += speed;
    }

    // Rotation
    double raw_theta = atan2(mouse_y - y, mouse_x - x);
    theta = rad_to_fixed(raw_theta);
}
