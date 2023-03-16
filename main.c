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
    curs_set(0);
    fld *main = init();
    render(main);
    fld_delete(main);
    endwin();
    return 0;
}