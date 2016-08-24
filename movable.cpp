#include "movable.h"

Movable::Movable(int x, int y, BITMAP* sprite)
{
    this->sprite = sprite;

    this->top = (y - (sprite->h / 2));
    this->left = (x - (sprite->w / 2));
    this->bottom = top + sprite->h;
    this->right = left + sprite->w;

    this->theta = 0;
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
