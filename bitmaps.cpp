#include "bitmaps.h"
#include "constants.h"

#include <allegro.h>

BITMAP* buffer = NULL;

int load_bitmaps()
{
    buffer = create_bitmap(WIDTH, HEIGHT);
    if (!buffer)
    {
        allegro_message("Could not create buffer\n");
        return 1;
    }

    return 0;
}

void free_bitmaps()
{
    destroy_bitmap(buffer);
}
