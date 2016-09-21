#include "player.h"
#include "constants.h"
#include "bitmaps.h"
#include "gamepad.h"

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
        if (key[KEY_A] && left > speed)
        {
            x -= round(speed / sqrt(2.0));
            y -= round(speed / sqrt(2.0));
        }
        else if (key[KEY_D] && right < WIDTH)
        {
            x += round(speed / sqrt(2.0));
            y -= round(speed / sqrt(2.0));
        }
        else
        {
            y -= speed;
        }
    }
    else if (key[KEY_S] && bottom < HEIGHT)
    {
        if (key[KEY_A] && left > speed)
        {
            x -= round(speed / sqrt(2.0));
            y += round(speed / sqrt(2.0));
        }
        else if (key[KEY_D] && right < WIDTH)
        {
            x += round(speed / sqrt(2.0));
            y += round(speed / sqrt(2.0));
        }
        else
        {
            y += speed;
        }
    }
    else if (key[KEY_A] && left > speed)
    {
        x -= speed;
    }
    else if (key[KEY_D] && right < WIDTH)
    {
        x += speed;
    }

    set_boundaries();

    // Rotation
    double raw_theta = atan2(mouse_y - y, mouse_x - x);
    theta = rad_to_fixed(raw_theta);
}

void Player::move(double raw_theta)
{
    float lx, ly;

    GamepadStickNormXY(GAMEPAD_0, STICK_LEFT, &lx, &ly);

    x += lx * speed;
    y -= ly * speed;

    set_boundaries();

    theta = rad_to_fixed(-raw_theta);
}
