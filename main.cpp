#include "constants.h"
#include "system.h"

#include <allegro.h>

int main()
{
    System sys;
    if (sys.init("Zombies!") != 0)
        return 1;

    while (!keypressed()) {}

    return 0;
}
END_OF_MAIN();
