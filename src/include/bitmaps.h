#ifndef BITMAPS_H
#define BITMAPS_H

#include <allegro.h>

extern BITMAP* buffer;
extern BITMAP* player_sprite;
extern BITMAP* zombie_sprite;
extern BITMAP* bullet_sprite;
extern BITMAP* background_sprite;

int load_bitmaps();
void free_bitmaps();

#endif
