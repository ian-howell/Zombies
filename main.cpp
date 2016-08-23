#include "constants.h"
#include "system.h"

#include <allegro.h>

int main()
{
    System sys;
    if (sys.init("Zombies!") != 0)
        return 1;

    int x = (WIDTH / 2) - (WIDTH / 4);
    int dir = 1;
    while (!keypressed())
    {
        clear_to_color(screen, makecol(0, 0, 0));
        circle(screen, x, HEIGHT / 2, 20, makecol(255, 0, 0));

        if (x + dir > 0.75 * WIDTH || x + dir < 0.25 * WIDTH)
            dir *= -1;

        x += dir;
    }

    return 0;
}
END_OF_MAIN();
