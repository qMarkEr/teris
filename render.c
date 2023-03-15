#include "render.h"
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "controls.h"
#include "figures.h"

void fld_output(int **frame) {
    clear();
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printw("%s", frame[i][j] == 0 ? ".." : "$$");
        }
        printw("\n");
    }
    refresh();
}

void fig_output(fld field, fig f, int stop) {
    if (!stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            int x = f.blocks[i].x;
            int y = f.blocks[i].y;
            if (x >= 0 && y >= 0)
                field.frame[y][x] = 1;
        }
        fld_output(field.frame);
        for (int i = 0; i < BLOCKS; ++i) {
            int x = f.blocks[i].x;
            int y = f.blocks[i].y;
            if (x >= 0 && y >= 0)
                field.frame[y][x] = 0;
        }

    }
}

void move_down(fld *f, fig *prev, int *stop) {
    for (int i = 0; i < BLOCKS && !(*stop); ++i) {
        pnt temp;
        temp.x = prev->blocks[i].x;
        temp.y = prev->blocks[i].y + 1;
        if (temp.y >= HEIGHT || collision(temp, *f)) {
            *stop = 1;
        }
    }
    if (*stop) {
        for (int j = 0; j < BLOCKS; ++j) {
            if (prev->blocks[j].y < 0) {
                *stop = 2;
                return;
            }
            f->frame[prev->blocks[j].y][prev->blocks[j].x] = 1;
            if (f->max_y > prev->blocks[j].y)
                f->max_y = prev->blocks[j].y;
        }
        clear_layer(f);
    } else {
        for (int i = 0; i < BLOCKS; ++i) {
            prev->blocks[i].y++;
        }
    }
}

void render(fld *field) {
    srand(time(NULL));
    struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
    int stop = 0;
    fig *j;
    char type = TYPES[rand() % 7];
    j = figure(type);
    spawn(j);
    int ticks = 30;
    while (stop != 2) {
        clock_gettime(CLOCK_MONOTONIC, &sp_start);
        if (stop) {
            type = TYPES[rand() % 7];
            j = figure(type);
            spawn(j);
            stop = 0;
        }
        char action = getch();
        if (action == 'a')
            shift(field, -1, j);

        if (action == 'd')
            shift(field, 1, j);

        if (action == 'w')
            rotate(field, j);

        if (action == 's')
            move_down(field, j, &stop);

        if (ticks == 0) {
            move_down(field, j, &stop);
            ticks = 30;
        }
        fig_output(*field, *j, stop);
        clock_gettime(CLOCK_MONOTONIC, &sp_end);
        if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
            (ts2.tv_nsec = 16000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
            nanosleep(&ts2, &ts1);
        ticks--;
    }
}