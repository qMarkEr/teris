#include "figures.h"
#include <stdlib.h>
#include "stdio.h"
#include "time.h"
#include "constants.h"
#include "ncurses.h"
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
    for (int i = 0; i < BLOCKS; ++i) {
        res->blocks[i].x += WIDTH / 2;
        res->blocks[i].y -= 2;
    }
    return res;
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
    new->play = 1;
    new->max_y = HEIGHT - 1;
    new->next = NULL;
    new->current = NULL;
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
    fig_delete(game->next);
    fig_delete(game->current);
    free(game);
}

void fig_delete(fig *f) {
    free(f->blocks);
    free(f);
}
