#include <curses.h>
#include <stdlib.h>
#include "render.h"
#include <time.h>
#include <stdio.h>
#include "figures.h"


int main() {
    srand(time(NULL));
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);
    menu("start_menu.txt");
    char act = getchar();
    while (act != 'q') {
        clear();
        fld *main = init();
        render(main);
        clear();
        refresh();
        menu("game_over.txt");
        move(3, 1);
        refresh();
        printf("your score: %d", main->count);
        fld_delete(main);
        act = getchar();
    }
    endwin();
    return 0;
}