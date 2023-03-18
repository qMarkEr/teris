#ifndef TETRIS_FIGURES_H
#define TETRIS_FIGURES_H


typedef struct point {
    int x;
    int y;
} pnt;

typedef struct figure {
    pnt *blocks;
    char type;
} fig;

typedef struct field {
    int **frame;
    int count;
    int high_count;
    int max_y;
    int lines_cleared;
    int level;
    fig* next;
    fig* current;
    int play;
} fld;

fig *figure(char name);

fld *init();

void fld_delete(fld *game);

void fig_delete(fig *f);

int collision(pnt f, fld *field);

#endif //TETRIS_FIGURES_H
