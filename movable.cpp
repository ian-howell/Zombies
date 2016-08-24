#include "movable.h"

Movable::Movable(int x, int y, BITMAP* sprite)
{
    this->sprite = sprite;

    this->top = (y - (sprite->h / 2));
    this->left = (x - (sprite->w / 2));
}

void Movable::draw(BITMAP* buffer)
{
    draw_sprite(buffer, sprite, left, top);
}
