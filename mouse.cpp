#include "mouse.h"

void draw_mouse(BITMAP* buffer)
{
    int len = 10;
    line(buffer, (mouse_x - len), mouse_y, (mouse_x + len), mouse_y, makecol(255, 0, 0));
    line(buffer, mouse_x, (mouse_y - len), mouse_x, (mouse_y + len), makecol(255, 0, 0));
    circle(buffer, mouse_x, mouse_y, (len / 2), makecol(255, 0, 0));
}
