#include "bullet.h"
#include "constants.h"
#include "bitmaps.h"

#include <cmath>

Bullet::Bullet(int x, int y) : Movable(x, y, bullet_sprite)
{
    double raw_theta = atan2(mouse_y - y, mouse_x - x);
    theta = rad_to_fixed(raw_theta);

    speed = 10;
}

Bullet::Bullet(int x, int y, double raw_theta) : Movable(x, y, bullet_sprite)
{
    theta = -rad_to_fixed(raw_theta);
    speed = 10;
}

void Bullet::move(int to_x, int to_y)
{
    x += fixtof(fixcos(theta)) * speed;
    y += fixtof(fixsin(theta)) * speed;


    set_boundaries();
}
