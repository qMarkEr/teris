#include "game_state.h"
#include "constants.h"
#include "time.h"
#include "render.h"
#include "ncurses.h"

void clear_layer(fld *f) {
    int count = 0;
    struct timespec sp_start, sp_end, ts1, ts2 = {0, 0};
    for (int i = HEIGHT - 1; i >= f->max_y;) {
        int flag = 1;
        while (flag) {
            for (int j = 0; j < WIDTH && flag; ++j)
                if (f->frame[i][j] == 0)
                    flag = 0;

            if (flag) {
                int t = 20;
                while(t >= 0) {
                    clock_gettime(CLOCK_MONOTONIC, &sp_start);
                    for (int j = 0; j < WIDTH; ++j) {
                        f->frame[i][j] = 0;
                    }
                    game_output(f);
                    refresh();
                    if(t == 0) {
                        for (int k = i; k >= f->max_y; --k)
                            for (int j = 0; j < WIDTH; ++j)
                                f->frame[k][j] = f->frame[k - 1][j];
                    }
                    clock_gettime(CLOCK_MONOTONIC, &sp_end);
                    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
                        (ts2.tv_nsec = 7000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
                        nanosleep(&ts2, &ts1);
                    t--;
                }
                f->max_y++;
                count++;
            } else {
                i--;
            }
        }
    }
    f->lines_cleared += count;
    if (f->lines_cleared >= 10 && f->level < 10) {
        f->level++;
        f->lines_cleared -= 10;
    }
    score(f, count);
}

void score(fld *f, int count) {
    while (count != 0) {
        if (count - 4 >= 0) {
            f->count += 1200;
            count -= 4;
        } else if (count - 3 >= 0) {
            f->count += 300;
            count -= 3;
        } else if (count - 2 >= 0) {
            f->count += 100;
            count -= 2;
        } else {
            f->count += 40;
            count--;
        }
    }
    if (f->count > f->high_count) {
        f->high_count = f->count;
    }
}

int add_figure(fld *field, fig f) {
    int status = 1;
    for (int j = 0; j < BLOCKS; ++j) {
        if (f.blocks[j].y < 0) {
            status = 2;
            break;
        }
        field->frame[f.blocks[j].y][f.blocks[j].x] = 1;
        if (field->max_y > f.blocks[j].y)
            field->max_y = f.blocks[j].y;
    }
    return status;
}