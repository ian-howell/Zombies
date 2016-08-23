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
    int newx = x + dx;
    int newy = y + dy;

    if (newx + r > WIDTH || newx - r < 0)
    {
        dx *= -1;
        newx = x + dx;
    }

    if (newy + r > HEIGHT || newy - r < 0)
    {
        dy *= -1;
        newy = y + dy;
    }

    x = newx;
    y = newy;
}

void Player::draw(BITMAP* buffer)
{
    circle(buffer, x, y, r, makecol(255, 0, 0));
}
