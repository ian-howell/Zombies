#include "constants.h"
#include "system.h"

#include <allegro.h>

volatile int ticks = 0;
void ticker() { ticks++; } END_OF_FUNCTION(ticker)

int main()
{
    System sys;
    if (sys.init("Zombies!") != 0)
        return 1;

    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(FPS));

    BITMAP* buffer = create_bitmap(WIDTH, HEIGHT);
    if (!buffer)
    {
        allegro_message("Could not create buffer\n");
        return 1;
    }

    int x = (WIDTH / 2) - (WIDTH / 4);
    int dir = 1;

    bool done = false;
    while (!done)
    {

        while (ticks == 0)
        {
            // rest until a full tick has passed
            rest(1);
        }

        while (ticks > 0)
        {
            int old_ticks = ticks;

            // logic
            if (key[KEY_ESC])
            {
                done = true;
                break;
            }

            if (x + dir > 0.75 * WIDTH || x + dir < 0.25 * WIDTH)
                dir *= -1;

            x += dir;

            // if the logic takes too long, abort and draw a frame
            ticks--;
            if (old_ticks <= ticks)
                break;
        }

        // draw everything
        clear_to_color(buffer, makecol(0, 0, 0));
        circle(buffer, x, HEIGHT / 2, 20, makecol(255, 0, 0));
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }

    return 0;
}
END_OF_MAIN();
