#include "controls.h"
#include "ncurses.h"
#include "constants.h"
#include "game_state.h"

void shift(fld *f, int direction) {
    int stop = 0;
    for (int i = 0; i < BLOCKS && !(stop); ++i) {
        pnt temp;
        temp.x = f->current->blocks[i].x + direction;
        temp.y = f->current->blocks[i].y;
        if (collision(temp, f)) {
            stop = HAS_COLLISION;
        }
    }
    if (!stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            f->current->blocks[i].x += direction;
        }
    }
}

void rotate(fld *f) {
    if (f->current->type == 'O') {
        return;
    }
    int shift_x = f->current->blocks[0].x;
    int shift_y = f->current->blocks[0].y;
    int stop = 0;
    for (int i = 0; i < BLOCKS && !(stop); ++i) {
        pnt temp;
        temp.y = f->current->blocks[i].x - shift_x + shift_y;
        temp.x = -(f->current->blocks[i].y - shift_y) + shift_x;
        if (collision(temp, f)) {
            stop = HAS_COLLISION;
        }
    }
    if (!stop) {
        for (int i = 0; i < BLOCKS; ++i) {
            int x = -(f->current->blocks[i].y - shift_y) + shift_x;
            f->current->blocks[i].y = f->current->blocks[i].x - shift_x + shift_y;
            f->current->blocks[i].x = x;
        }
    }
}

void move_fig(fld *field, int *stop) {
    char action = getch();
    switch (action) {
        case 'a':
            shift(field, -1);
            break;
        case 'd':
            shift(field, 1);
            break;
        case 'w':
            rotate(field);
            break;
        case 's':
            move_down(field, stop);
            break;
        case 'p':
            field->play = 0;
            break;
        case 'q':
            save_state(field);
            *stop = GAME_OVER;
            break;
        default:
            break;
    }
}

void move_down(fld *f, int *stop) {
    for (int i = 0; i < BLOCKS && !(*stop); ++i) {
        pnt temp;
        temp.x = f->current->blocks[i].x;
        temp.y = f->current->blocks[i].y + 1;
        if (temp.y >= HEIGHT || collision(temp, f)) {
            *stop = HAS_COLLISION;
        }
    }
    if (*stop) {
        *stop = add_figure(f);
        clear_layer(f);
    } else {
        for (int i = 0; i < BLOCKS; ++i) {
            f->current->blocks[i].y++;
        }
    }
}

