#include "render.h"
#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "constants.h"
#include "controls.h"
#include "figures.h"



void game_output(fld *f) {

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvaddstr(i, j * 2, f->frame[i][j] == 0 ? ".." : "$$");
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
        if (i == 12) {
            if(f->play == 0)
                printw("\tpause");
            else
                printw("\t     ");
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
                mvaddstr(y, x * 2, "$$");
        }
    }
}

void render(fld *field) {
    struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
    int stop = 0;
    srand(time(NULL));
    char name = TYPES[rand() % 7];
    if (field->current == NULL) {
        field->current = figure(name);
        name = TYPES[rand() % 7];
        next_fig(field, name, stop);
    } else {
        for (int i = 0; i < BLOCKS; ++i) {
            field->next->blocks[i].x += 8;
            field->next->blocks[i].y += 10;
        }    }

    int ticks = START_SPEED;
    while(stop != GAME_OVER) {
        while (field->play && stop != GAME_OVER) {
            clock_gettime(CLOCK_MONOTONIC, &sp_start);
            if (stop == HAS_COLLISION) {
                fig_delete(field->current);
                field->current = figure(field->next->type);
                name = TYPES[rand() % 7];
                next_fig(field, name, stop);
                stop = 0;
            }
            move_fig(field, &stop);
            if (ticks == 0) {
                move_down(field, &stop);
                ticks = START_SPEED - field->level * 10;
            }
            game_output(field);
            fig_output(field->current, stop);
            refresh();
            clock_gettime(CLOCK_MONOTONIC, &sp_end);
            if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
                (ts2.tv_nsec = 5000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
                nanosleep(&ts2, &ts1);
            ticks--;

        }
        if(stop != GAME_OVER && getchar() == 'p')
            field->play = 1;
    }
}

void next_fig(fld *field, char name, int stop) {
    if (stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            mvaddstr(field->next->blocks[i].y, field->next->blocks[i].x * 2, "  ");
        }
        fig_delete(field->next);
    }
    field->next = figure(name);
    for (int i = 0; i < BLOCKS; ++i) {
        field->next->blocks[i].x += 8;
        field->next->blocks[i].y += 10;
    }
}

void menu(char* menu) {
    FILE* fptr = fopen(menu, "r");
    char c = fgetc(fptr);
    while(c != EOF) {
        putchar(c);
        c = fgetc(fptr);
    }
    fclose(fptr);
}
