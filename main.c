#include <curses.h>
#include <stdlib.h>
#include "render.h"
#include <time.h>
#include "figures.h"


int main() {
    srand(time(NULL));
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    fld *main = init();
//    for (int i = 0; i < WIDTH; ++i) {
//        main->frame[HEIGHT - 1][i] = 1;
//        main->frame[HEIGHT - 2][i] = 1;
//        main->frame[HEIGHT - 3][i] = 1;
//    }
//    main->frame[HEIGHT - 2][5] = 0;
   // main->max_y = HEIGHT - 3;
    render(main);
    fld_delete(main);
    endwin();
    return 0;
}