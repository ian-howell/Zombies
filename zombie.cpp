#include "zombie.h"
#include "constants.h"
#include "bitmaps.h"

#include <ctime>
#include <cstdlib>
#include <cmath>

Zombie::Zombie(int x, int y) : Movable(x, y, zombie_sprite)
{
    speed = (rand() % 3) + 4;
}

void Zombie::move(int to_x, int to_y)
{
    // Rotation
    double raw_theta = atan2(to_y - y, to_x - x);
    theta = rad_to_fixed(raw_theta);

    x += fixtof(fixcos(theta)) * speed;
    y += fixtof(fixsin(theta)) * speed;

    left = x - sprite->w / 2.0;
    right = x + sprite->w / 2.0;

    top = y - sprite->h / 2.0;
    bottom = y + sprite->h / 2.0;
}
