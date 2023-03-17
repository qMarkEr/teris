#include <ncurses.h>
#include "render.h"
#include <stdio.h>
#include "figures.h"


int main() {
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);
    menu("start_menu.txt");
    char act = getchar();
    while (act != 'q') {
        clear();
        if (act == 'p') {
            fld *main = init();
            render(main);
            clear();
            refresh();
            menu("game_over.txt");
            move(14, 4);
            printf("your score: %d", main->count);
            fld_delete(main);
            refresh();
        }
        act = getchar();
    }
    endwin();
    return 0;
}