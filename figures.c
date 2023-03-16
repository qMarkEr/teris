#include "figures.h"
#include <stdlib.h>
#include "stdio.h"
#include "ncurses.h"
#include "time.h"
#include "render.h"

fig *figure(char name) {

    fig *res = (fig *) malloc(sizeof(fig));
    res->blocks = (pnt *) malloc(sizeof(pnt) * BLOCKS);
    res->type = name;
    switch (name) {
        case 'I':
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = -2, res->blocks[1].y = 0;
            res->blocks[2].x = -1, res->blocks[2].y = 0;
            res->blocks[3].x = 1, res->blocks[3].y = 0;
            break;
        case 'J':
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = -1, res->blocks[1].y = 0;
            res->blocks[2].x = -1, res->blocks[2].y = -1;
            res->blocks[3].x = 1, res->blocks[3].y = 0;
            break;
        case 'L':
            res->blocks[2].x = -1, res->blocks[2].y = 0;
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = 1, res->blocks[1].y = 0;
            res->blocks[3].x = 1, res->blocks[3].y = -1;
            break;
        case 'O':
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = -1, res->blocks[1].y = 0;
            res->blocks[2].x = -1, res->blocks[2].y = -1;
            res->blocks[3].x = 0, res->blocks[3].y = -1;
            break;
        case 'S':
            res->blocks[2].x = -1, res->blocks[2].y = 0;
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = 0, res->blocks[1].y = -1;
            res->blocks[3].x = 1, res->blocks[3].y = -1;
            break;
        case 'T':
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = 0, res->blocks[1].y = -1;
            res->blocks[2].x = -1, res->blocks[2].y = 0;
            res->blocks[3].x = 1, res->blocks[3].y = 0;
            break;
        case 'Z':
            res->blocks[0].x = 0, res->blocks[0].y = 0;
            res->blocks[1].x = 0, res->blocks[1].y = -1;
            res->blocks[2].x = -1, res->blocks[2].y = -1;
            res->blocks[3].x = 1, res->blocks[3].y = 0;
            break;
        default:
            break;
    }
    spawn(res);
    return res;
}

void spawn(fig *figure) {
    for (int i = 0; i < BLOCKS; ++i) {
        figure->blocks[i].x += WIDTH / 2;
        figure->blocks[i].y -= 2;
    }
}

int collision(pnt f, fld *field) {
    int flag = 0;
    int i = f.y, j = f.x;
    if (i >= 0 && (j < 0 || j >= WIDTH || field->frame[i][j] == 1)) {
        flag = 1;
    }
    return flag;
}

fld *init() {
    fld *new = (fld *) malloc(sizeof(fld));
    new->frame = (int **) malloc(sizeof(int *) * HEIGHT);
    for (int i = 0; i < HEIGHT; ++i) {
        new->frame[i] = (int *) malloc(sizeof(int) * WIDTH);
        for (int j = 0; j < WIDTH; ++j) {
            new->frame[i][j] = 0;
        }
    }
    FILE *file = fopen("score.txt", "r");
    fscanf(file, "%d", &new->high_count);
    fclose(file);
    new->count = 0;
    new->lines_cleared = 0;
    new->level = 0;
    new->max_y = HEIGHT - 1;
    return new;
}

void fld_delete(fld *game) {
    FILE *file = fopen("score.txt", "w");
    fprintf(file, "%d", game->high_count);
    fclose(file);
    for (int i = 0; i < HEIGHT; ++i) {
        free(game->frame[i]);
    }
    free(game->frame);
    free(game);
}

void fig_delete(fig *f) {
    free(f->blocks);
    free(f);
}

void clear_layer(fld *f) {
    int count = 0;
    for (int i = HEIGHT - 1; i >= f->max_y;) {
        int flag = 1;
        while (flag) {
            for (int j = 0; j < WIDTH && flag; ++j)
                if (f->frame[i][j] == 0)
                    flag = 0;
            if (flag) {
                for (int k = i; k >= f->max_y; --k)
                    for (int j = 0; j < WIDTH; ++j)
                        f->frame[k][j] = f->frame[k - 1][j];
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