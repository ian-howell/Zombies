#include "bitmaps.h"
#include "constants.h"
#include "datafile_header.h"

#include <allegro.h>

BITMAP* buffer = NULL;
BITMAP* player_sprite = NULL;
BITMAP* zombie_sprite = NULL;
BITMAP* bullet_sprite = NULL;
BITMAP* background_sprite = NULL;
DATAFILE* datafile = NULL;

int load_bitmaps()
{
    buffer = create_bitmap(WIDTH, HEIGHT);
    if (!buffer)
    {
        allegro_message("Could not create buffer\n");
        return 1;
    }

    datafile = load_datafile("datafile.dat");
    if (!datafile)
    {
        allegro_message("Could not load datafile\n");
        return 1;
    }


    player_sprite = (BITMAP*)datafile[PLAYER_SPRITE].dat;
    zombie_sprite = (BITMAP*)datafile[ZOMBIE_SPRITE].dat;
    bullet_sprite = (BITMAP*)datafile[BULLET_SPRITE].dat;
    background_sprite = (BITMAP*)datafile[BACKGROUND_SPRITE].dat;

    return 0;
}

void free_bitmaps()
{
    destroy_bitmap(buffer);
    unload_datafile(datafile);
}
