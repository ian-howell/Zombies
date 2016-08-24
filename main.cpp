#include "constants.h"
#include "system.h"
#include "bitmaps.h"
#include "player.h"

#include <allegro.h>

enum
{
    TITLE,
    PLAY,
    PAUSE,
};

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

    extern BITMAP* buffer;
    extern BITMAP* background_sprite;
    load_bitmaps();

    int font_height = text_height(font);

    bool key_debounce[KEY_MAX];

    Player player(WIDTH / 2, HEIGHT / 2);

    char state = TITLE;

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
            switch (state)
            {
                case TITLE:
                    if (key[KEY_ENTER])
                        state = PLAY;
                    break;
                case PLAY:
                    player.move();

                    if (key[KEY_P] && !key_debounce[KEY_P])
                    {
                        state = PAUSE;
                        key_debounce[KEY_P] = true;
                    }
                    if (!key[KEY_P])
                        key_debounce[KEY_P] = false;

                    break;
                case PAUSE:
                    if (key[KEY_ESC])
                    {
                        done = true;
                        break;
                    }
                    if (key[KEY_P] && !key_debounce[KEY_P])
                    {
                        state = PLAY;
                        key_debounce[KEY_P] = true;
                    }
                    if (!key[KEY_P])
                        key_debounce[KEY_P] = false;
                    break;
            }


            // if the logic takes too long, abort and draw a frame
            ticks--;
            if (old_ticks <= ticks)
                break;
        }

        // draw everything

        switch (state)
        {
            case TITLE:
                clear_to_color(buffer, makecol(0, 0, 0));
                textout_centre_ex(buffer, font, "ZOMBIES!", WIDTH / 2,
                        (HEIGHT / 2) - font_height,
                        makecol(255, 0, 0), -1);
                textout_centre_ex(buffer, font, "Press ENTER to begin", WIDTH / 2,
                        (HEIGHT / 2) + font_height,
                        makecol(255, 0, 0), -1);
                break;
            case PLAY:
                draw_sprite(buffer, background_sprite, 0, 0);
                player.draw(buffer);
                break;
            case PAUSE:
                textout_centre_ex(buffer, font, "PAUSE", WIDTH / 2,
                        (HEIGHT / 2) - font_height,
                        makecol(0, 0, 0), -1);
                textout_centre_ex(buffer, font, "Press ESC to exit", WIDTH / 2,
                        (HEIGHT / 2) + font_height,
                        makecol(0, 0, 0), -1);
                break;
        }

        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }

    free_bitmaps();

    return 0;
}
END_OF_MAIN();
