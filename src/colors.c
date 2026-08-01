#include <ncurses.h>
#include "../include/colors.h"

void init_colors(void)
{
    start_color();

    init_pair(
        COLOR_DEFAULT,
        COLOR_WHITE,
        COLOR_BLACK
    );

    init_pair(
        COLOR_CORRECT,
        COLOR_BLACK,
        COLOR_GREEN
    );

    init_pair(
        COLOR_WRONG,
        COLOR_BLACK,
        COLOR_RED
    );

    init_pair(
        COLOR_PRESENT,
        COLOR_BLACK,
        COLOR_YELLOW
    );
}
