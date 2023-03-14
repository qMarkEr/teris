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
    fld *main = init();
    for (int i = 0; i < 2; ++i) {
        char c = TYPES[rand() % 7];
        fig* j = figure(c);
        spawn(j);
        render(main, j);
        fig_delete(j);
    }
    fld_delete(main);
    endwin();
    return 0;
}

