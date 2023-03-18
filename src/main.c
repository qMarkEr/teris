#include <ncurses.h>
#include "render.h"
#include <stdio.h>
#include "figures.h"
#include "constants.h"

void read_state(fld *field, FILE *fptr) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            field->frame[i][j] = fgetc(fptr) - '0';
        }
    }
    fscanf(fptr, "%d\n", &field->count);
    fscanf(fptr, "%d\n", &field->max_y);
    fscanf(fptr, "%d\n", &field->lines_cleared);
    fscanf(fptr, "%d\n", &field->level);
    char c, n;
    fscanf(fptr, "%c\n", &c);

    field->current = figure(c);
    int shift_x;
    int shift_y;
    fscanf(fptr, "%d\n", &shift_x);
    fscanf(fptr, "%d\n", &shift_y);
    fscanf(fptr, "%c\n", &n);
    for (int i = 0; i < BLOCKS; ++i) {
        field->current->blocks[i].x += shift_x;
        field->current->blocks[i].y += shift_y;
    }
    field->next = figure(n);
}


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
        if (act == 'p' || act == 'c') {
            int play = 1;
            fld *main = init();
            if (act == 'c') {
                FILE *fptr = fopen("prev_state.txt", "r");
                if (fptr == NULL) {
                    play = 0;
                } else {
                    fseek(fptr, 0, SEEK_END);
                    long size = ftell(fptr);
                    if (size != 0) {
                        fseek(fptr, 0, SEEK_SET);
                        read_state(main, fptr);
                        fclose(fptr);
                    } else {
                        play = 0;
                    }
                }
            }
            if (play) {
                render(main);
                clear();
                refresh();
                menu("game_over.txt");
                move(14, 4);
                printf("your score: %d", main->count);
                refresh();
            }
                fld_delete(main);
        }
        act = getchar();
    }
    endwin();
    return 0;
}