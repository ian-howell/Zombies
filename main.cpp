#include "constants.h"
#include "system.h"
#include "bitmaps.h"
#include "player.h"

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

    Player player;

    extern BITMAP* buffer;
    load_bitmaps();

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

            player.move();

            // if the logic takes too long, abort and draw a frame
            ticks--;
            if (old_ticks <= ticks)
                break;
        }

        // draw everything
        clear_to_color(buffer, makecol(0, 0, 0));
        player.draw(buffer);
        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }

    free_bitmaps();

    return 0;
}
END_OF_MAIN();
