#ifndef CONSTANTS_H
#define CONSTANTS_H

#define rad_to_fixed(x) ftofix((x) * 128 / M_PI)
#define MID_X (WIDTH / 2)
#define MID_Y (HEIGHT / 2)

const int WIDTH = 640;
const int HEIGHT = 480;

const int SPAWN_RATE = 40;
const int SHOT_DELAY = 10;

const int FPS = 30;

#endif
