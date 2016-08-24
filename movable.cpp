#include "movable.h"

Movable::Movable(int top, int left)
{
    this->top = top;
    this->left = left;
}

void Movable::draw(BITMAP* buffer)
{
    draw_sprite(buffer, sprite, left, top);
}
