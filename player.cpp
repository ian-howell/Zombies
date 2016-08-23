#include "player.h"
#include "constants.h"

Player::Player(int x, int y, int r) : Movable(x, y)
{
    this->r = r;

    dx = 2;
    dy = 2;
}

void Player::move()
{
    if (key[KEY_W] && ((y - r) - dy) > 0)
        y -= dy;
    if (key[KEY_S] && (y + r + dy) < HEIGHT)
        y += dy;
    if (key[KEY_A] && ((x - r) - dx) > 0)
        x -= dx;
    if (key[KEY_D] && (x + r + dx) < WIDTH)
        x += dx;
}

void Player::draw(BITMAP* buffer)
{
    circle(buffer, x, y, r, makecol(255, 0, 0));
}
