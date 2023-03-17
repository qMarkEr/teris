#include "controls.h"
#include "ncurses.h"
#include "constants.h"
#include "game_state.h"

void shift(fld *f, int direction, fig *prev) {
    int stop = 0;
    for (int i = 0; i < BLOCKS && !(stop); ++i) {
        pnt temp;
        temp.x = prev->blocks[i].x + direction;
        temp.y = prev->blocks[i].y;
        if (collision(temp, f)) {
            stop = 1;
        }
    }
    if (!stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            prev->blocks[i].x += direction;
        }
    }
}

void rotate(fld *f, fig *prev) {
    if (prev->type == 'O') {
        return;
    }
    int shift_x = prev->blocks[0].x;
    int shift_y = prev->blocks[0].y;
    int stop = 0;
    for (int i = 0; i < BLOCKS && !(stop); ++i) {
        pnt temp;
        temp.y = prev->blocks[i].x - shift_x + shift_y;
        temp.x = -(prev->blocks[i].y - shift_y) + shift_x;
        if (collision(temp, f)) {
            stop = 1;
        }
    }
    if (!stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            int x = -(prev->blocks[i].y - shift_y) + shift_x;
            prev->blocks[i].y = prev->blocks[i].x - shift_x + shift_y;
            prev->blocks[i].x = x;
        }
    }
}

void move_fig(fld *field, fig *f, int *stop) {
    char action = getch();
    switch (action) {
        case 'a':
            shift(field, -1, f);
            break;
        case 'd':
            shift(field, 1, f);
            break;
        case 'w':
            rotate(field, f);
            break;
        case 's':
            move_down(field, f, stop);
            break;
        case 'p':
            field->play = 0;
            break;
        case 'q':
            *stop = 2;
            break;
        default:
            break;
    }
}

void move_down(fld *f, fig *prev, int *stop) {
    for (int i = 0; i < BLOCKS && !(*stop); ++i) {
        pnt temp;
        temp.x = prev->blocks[i].x;
        temp.y = prev->blocks[i].y + 1;
        if (temp.y >= HEIGHT || collision(temp, f)) {
            *stop = 1;
        }
    }
    if (*stop) {
        *stop = add_figure(f, *prev);
        clear_layer(f);
    } else {
        for (int i = 0; i < BLOCKS; ++i) {
            prev->blocks[i].y++;
        }
    }
}

