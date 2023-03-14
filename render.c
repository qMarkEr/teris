#include "render.h"
#include <curses.h>
#include <unistd.h>
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
    for (int i = 0; i < BLOCKS; ++i) {
        int x = f.blocks[i].x;
        int y = f.blocks[i].y;
        if (x >= 0 && y >= 0)
            field.frame[y][x] = 1;
    }
    fld_output(field.frame);
    if (!stop) {
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

void render(fld *field, fig *f) {
    int stop = 0;
    while (!stop) {
        int speed = 3;
        char c = getch();
        if (c == 'a') {
            shift(field, -1, f);
        }
        if (c == 'd') {
            shift(field, 1, f);
        }
        if (c == 'w') {
            rotate(field, f);
        }
        if (c == 's') {
            speed = 1;
        }
        fig_output(*field, *f, stop);
        usleep(speed * 100000);
        move_down(field, f, &stop);
        fld_output(field->frame);
        printw("%d", field->max_y);
        //refresh();
    }
}