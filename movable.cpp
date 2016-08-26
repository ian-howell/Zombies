#include "movable.h"
#include "constants.h"

Movable::Movable(int x, int y, BITMAP* sprite)
{
    this->sprite = sprite;

    this->x = x;
    this->y = y;

    this->top = (y - (sprite->h / 2));
    this->left = (x - (sprite->w / 2));
    this->bottom = top + sprite->h;
    this->right = left + sprite->w;

    this->theta = 0;
}

void Movable::set_pos(int x, int y)
{
    this->x = x;
    this->y = y;
    set_boundaries();
}

void Movable::set_boundaries()
{
    left = x - sprite->w / 2.0;
    right = x + sprite->w / 2.0;

    top = y - sprite->h / 2.0;
    bottom = y + sprite->h / 2.0;
}

bool Movable::overlaps(const Movable& other, int tol)
{
    bool is_overlapping = (this->top + tol < other.bottom) &&
                          (this->bottom - tol > other.top) &&
                          (this->left + tol < other.right) &&
                          (this->right - tol > other.left);

    return is_overlapping;
}

bool Movable::in_bounds()
{
    return (top > 0) &&
           (bottom < HEIGHT) &&
           (left > 0) &&
           (right < WIDTH);
}

void Movable::draw(BITMAP* buffer)
{
    rotate_sprite(buffer, sprite, left, top, theta);

    /* // Draw the bounding box */
    /* line(buffer, left, top, right, top, makecol(255, 0, 0)); */
    /* line(buffer, left, top, left, bottom, makecol(255, 0, 0)); */
    /* line(buffer, right, top, right, bottom, makecol(255, 0, 0)); */
    /* line(buffer, left, bottom, right, bottom, makecol(255, 0, 0)); */

}
