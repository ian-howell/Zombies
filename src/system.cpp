#include "system.h"
#include "constants.h"

#include <allegro.h>

System::System()
{
    // Intentionally empty
}

int System::init(const char* title)
{
    if (allegro_init() != 0)
    {
        allegro_message("Couldn't initialize Allegro.\n");
        return 1;
    }

    set_window_title(title);

    if (install_keyboard())
    {
        allegro_message("Couldn't initialize keyboard.\n");
        return 1;
    }

    if (install_mouse() < 0)
    {
        allegro_message("Couldn't initialize mouse.\n");
        return 1;
    }

    if (install_timer())
    {
        allegro_message("Couldn't initialize timer.\n");
        return 1;
    }

    // For now, we use GFX_SAFE (it's the only thing that works on my pc)
    set_color_depth(32);
    if (set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0))
    {
        set_color_depth(24);
        if (set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0))
        {
            set_color_depth(16);
            if (set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0))
            {
                set_color_depth(15);
                if (set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0))
                {
                    allegro_message("Video Error: %s.\n", allegro_error);
                    return 1;
                }
            }
        }
    }

    return 0;
}
