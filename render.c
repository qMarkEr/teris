#include "render.h"
#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "controls.h"
#include "figures.h"

#define START_SPEED 100

void game_output(fld *f) {

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvaddch(i, j, f->frame[i][j] == 0 ? '.' : '$');
        }
        if (i == 1) {
            printw("\tScore: %d", f->count);
        }
        if (i == 3) {
            printw("\tHigh score: %d", f->high_count);
        }
        if (i == 5) {
            printw("\tLevel: %d", f->level);
        }
        fig_output(f->next, 0);
    }

}


void fig_output(fig *f, int stop) {
    if (!stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            int x = f->blocks[i].x;
            int y = f->blocks[i].y;
            if (x >= 0 && y >= 0)
                mvaddch(y, x, '$');
        }
    }
}

void render(fld *field) {
    struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
    int stop = 0;
    srand(time(NULL));
    char name = TYPES[rand() % 7];
    fig *j = figure(name);
    name = TYPES[rand() % 7];
    field->next = figure(name);
    for (int i = 0; i < BLOCKS; ++i) {
        field->next->blocks[i].x += 12;
        field->next->blocks[i].y += 10;
    }
    int ticks = START_SPEED;
    int speed;
    while (stop != 2) {
        clock_gettime(CLOCK_MONOTONIC, &sp_start);
        if (stop) {
            fig_delete(j);
            j = figure(name);
            stop = 0;
            for (int i = 0; i < BLOCKS; ++i) {
                mvaddch(field->next->blocks[i].y, field->next->blocks[i].x,  ' ');
            }
            name = TYPES[rand() % 7];
            field->next = figure(name);

            for (int i = 0; i < BLOCKS; ++i) {
                field->next->blocks[i].x += 15;
                field->next->blocks[i].y += 10;
            }
        }
        move_fig(field, j, &stop);
        if (ticks == 0) {
            move_down(field, j, &stop);
            ticks = START_SPEED - field->level * 10;
        }
        game_output(field);
        fig_output(j, stop);
        refresh();
        clock_gettime(CLOCK_MONOTONIC, &sp_end);
        if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
            (ts2.tv_nsec = 5000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
            nanosleep(&ts2, &ts1);
        ticks--;
    }
    fig_delete(j);
}