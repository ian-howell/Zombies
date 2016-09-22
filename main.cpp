#include "constants.h"
#include "system.h"
#include "bitmaps.h"
#include "player.h"
#include "zombie.h"
#include "bullet.h"
#include "mouse.h"
#include "gamepad.h"
#include "scores.h"

#include <cstdlib>
#include <time.h>
#include <list>
#include <allegro.h>

enum
{
    TITLE,
    PLAY,
    PAUSE,
    GAME_OVER,
};

const char* SCORE_FILE = ".scores.txt";

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

    int font_h = text_height(font);

    bool key_debounce[KEY_MAX];

    Player player(MID_X, MID_Y);

    std::list<Zombie*> zombies;
    std::list<Zombie*>::iterator z_it;

    std::list<Bullet*> bullets;
    std::list<Bullet*>::iterator b_it;

    srand(time(NULL));

    // The rate at which zombies spawn in
    int spawn_timer = SPAWN_RATE;

    // The amount of time remaining until the player can shoot again
    int shot_delay = 0;

    // The angle in which the player is facing. Only used when the controller
    // is being used
    float old_angle = 0.0;

    int score = 0;
    int hiscore = read_highscores(SCORE_FILE);

    char state = TITLE;

    // Gamepad connection status
    bool gp_con;
    bool using_gp = false;
    GamepadInit();

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

            GamepadUpdate();

            // Check if the gamepad is connected
            gp_con = GamepadIsConnected(GAMEPAD_0);

            // logic
            switch (state)
            {
                case TITLE:
                    if (gp_con && GamepadButtonTriggered(GAMEPAD_0, BUTTON_START))
                    {
                        state = PLAY;
                        using_gp = true;
                        break;
                    }

                    if (mouse_b & 1 || key[KEY_ENTER])
                        state = PLAY;

                    if (key[KEY_ESC])
                        done = true;
                    else if (gp_con && GamepadButtonTriggered(GAMEPAD_0, BUTTON_BACK))
                        done = true;

                    break;

                case PLAY:

                    if (using_gp && gp_con)
                    {
                        // Update the player's angle if the right stick is being pressed
                        if (GamepadStickLength(GAMEPAD_0, STICK_RIGHT) > 0)
                            old_angle = GamepadStickAngle(GAMEPAD_0, STICK_RIGHT);

                        // Update the player's position and angle
                        player.move(old_angle);

                        if (shot_delay <= 0 && gp_con && GamepadStickLength(GAMEPAD_0, STICK_RIGHT) > 0 )
                        {
                            bullets.push_back(new Bullet(player.getx(), player.gety(), GamepadStickAngle(GAMEPAD_0, STICK_RIGHT)));
                            shot_delay = SHOT_DELAY;
                        }
                        else if (shot_delay > 0)
                        {
                            shot_delay--;
                        }
                    }
                    else
                    {
                        player.move();

                        if (shot_delay <= 0 && mouse_b & 1)
                        {
                            bullets.push_back(new Bullet(player.getx(), player.gety()));
                            shot_delay = SHOT_DELAY;
                        }
                        else if (shot_delay > 0)
                        {
                            shot_delay--;
                        }
                    }

                    for (b_it = bullets.begin(); b_it != bullets.end(); b_it++)
                    {
                        (*b_it)->move();

                        bool hit = false;
                        for (z_it = zombies.begin(); z_it != zombies.end(); z_it++)
                        {
                            if ((*z_it)->overlaps(*(*b_it)))
                            {
                                delete *z_it;
                                zombies.erase(z_it);
                                hit = true;
                                score += 100;
                                break;
                            }
                        }

                        if (hit || !(*b_it)->in_bounds())
                        {
                            delete *b_it;
                            bullets.erase(b_it++);
                        }
                    }

                    if (rand() % spawn_timer == 0)
                    {
                        // reset the timer
                        spawn_timer = SPAWN_RATE;

                        // Pick a random location along one of the walls
                        int wall = rand() % 4;
                        int randx = MID_X;
                        int randy = MID_Y;

                        if (wall == 0)
                        {
                            randy = rand() % HEIGHT;
                            randx = 0;
                        }
                        else if (wall == 1)
                        {
                            randx = rand() % WIDTH;
                            randy = 0;
                        }
                        else if (wall == 2)
                        {
                            randy = rand() % HEIGHT;
                            randx = WIDTH;
                        }
                        else if (wall == 3)
                        {
                            randx = rand() % WIDTH;
                            randy = HEIGHT;
                        }

                        // Spawn a zombie at the new location
                        zombies.push_back(new Zombie(randx, randy));
                    }
                    else
                    {
                        spawn_timer--;
                    }

                    for (z_it = zombies.begin(); z_it != zombies.end(); z_it++)
                    {
                        (*z_it)->move(player.getx(), player.gety());
                        if ((*z_it)->overlaps(player, 10))
                        {
                            state = GAME_OVER;
                            break;
                        }
                    }

                    if (using_gp)
                    {
                        if (GamepadButtonTriggered(GAMEPAD_0, BUTTON_START))
                            state = PAUSE;
                    }
                    else
                    {
                        if (key[KEY_P] && !key_debounce[KEY_P])
                        {
                            state = PAUSE;
                            key_debounce[KEY_P] = true;
                        }

                        if (!key[KEY_P])
                            key_debounce[KEY_P] = false;
                    }
                    break;

                case PAUSE:
                    if (key[KEY_ESC] || (gp_con && GamepadButtonTriggered(GAMEPAD_0, BUTTON_BACK)))
                    {
                        for (z_it = zombies.begin(); z_it != zombies.end(); z_it++)
                            delete *z_it;

                        for (b_it = bullets.begin(); b_it != bullets.end(); b_it++)
                            delete *b_it;

                        done = true;
                    }

                    if (using_gp)
                    {
                        if (GamepadButtonTriggered(GAMEPAD_0, BUTTON_START))
                            state = PLAY;
                    }
                    else
                    {
                        if (key[KEY_P] && !key_debounce[KEY_P])
                        {
                            state = PLAY;
                            key_debounce[KEY_P] = true;
                        }
                        if (!key[KEY_P])
                            key_debounce[KEY_P] = false;
                    }
                    break;

                case GAME_OVER:
                    for (z_it = zombies.begin(); z_it != zombies.end(); z_it++)
                        delete *z_it;
                    zombies.clear();

                    for (b_it = bullets.begin(); b_it != bullets.end(); b_it++)
                        delete *b_it;
                    bullets.clear();

                    // Save the high score
                    if (score > hiscore)
                    {
                        hiscore = score;
                        write_highscores(SCORE_FILE, hiscore);
                    }


                    if (using_gp)
                    {
                        if (GamepadButtonTriggered(GAMEPAD_0, BUTTON_START))
                        {
                            // Reset the score for next game
                            score = 0;

                            player.set_pos(MID_X, MID_Y);

                            state = PLAY;
                        }
                        else if (GamepadButtonTriggered(GAMEPAD_0, BUTTON_BACK))
                        {
                            done = true;
                        }
                    }
                    else
                    {
                        if (key[KEY_R])
                        {
                            // Reset the score for next game
                            score = 0;

                            player.set_pos(MID_X, MID_Y);

                            state = PLAY;
                        }

                        if (key[KEY_ESC])
                        {
                            done = true;
                        }
                    }
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
                textout_centre_ex(buffer, font, "ZOMBIES!", MID_X,
                        MID_Y - font_h,
                        makecol(255, 0, 0), -1);
                textout_centre_ex(buffer, font, "Press ENTER or click for keyboard/mouse",
                        MID_X, MID_Y + font_h,
                        makecol(255, 255, 255), -1);
                textout_centre_ex(buffer, font, "Press Start to use the controller", MID_X,
                        MID_Y + (3 * font_h),
                        makecol(255, 255, 255), -1);
                textout_centre_ex(buffer, font, "Press ESC or Back to exit", MID_X,
                        MID_Y + (5 * font_h),
                        makecol(255, 255, 255), -1);
                break;

            case PLAY:
                draw_sprite(buffer, background_sprite, 0, 0);

                for (b_it = bullets.begin(); b_it != bullets.end(); b_it++)
                    (*b_it)->draw(buffer);

                player.draw(buffer);

                for (z_it = zombies.begin(); z_it != zombies.end(); z_it++)
                    (*z_it)->draw(buffer);

                if (!using_gp)
                    draw_mouse(buffer);

                textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "%-12s %d",
                        "High Score:", hiscore);
                textprintf_ex(buffer, font, 0, font_h, makecol(0, 0, 0), -1, "%-12s %d",
                        "Score:", score);
                break;

            case PAUSE:
                textout_centre_ex(buffer, font, "PAUSE", MID_X,
                        MID_Y - font_h, makecol(0, 0, 0), -1);
                if (using_gp)
                {
                    textout_centre_ex(buffer, font, "Press Back to exit", MID_X,
                            MID_Y + font_h, makecol(0, 0, 0), -1);
                }
                else
                {
                    textout_centre_ex(buffer, font, "Press ESC to exit", MID_X,
                            MID_Y + font_h, makecol(0, 0, 0), -1);
                }
                break;

            case GAME_OVER:
                clear_to_color(buffer, makecol(0, 0, 0));

                if (score >= hiscore)
                {
                    textprintf_centre_ex(buffer, font, MID_X,
                            MID_Y - (3 * font_h), makecol(128, 255, 0), -1,
                            "New high score: %d!", score);
                }

                textout_centre_ex(buffer, font, "GAME OVER", MID_X,
                        MID_Y - font_h, makecol(255, 0, 0), -1);

                if (using_gp)
                {
                    textout_centre_ex(buffer, font, "Press Start to retart", MID_X,
                            MID_Y + font_h, makecol(255, 255, 255), -1);
                    textout_centre_ex(buffer, font, "Press Back to exit", MID_X,
                            MID_Y + (3 * font_h), makecol(255, 255, 255), -1);
                }
                else
                {
                    textout_centre_ex(buffer, font, "Press R to retart", MID_X,
                            MID_Y + font_h, makecol(255, 255, 255), -1);
                    textout_centre_ex(buffer, font, "Press ESC to exit", MID_X,
                            MID_Y + (3 * font_h), makecol(255, 255, 255), -1);
                }
                break;
        }

        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
    }

    free_bitmaps();

    return 0;
}
END_OF_MAIN();
