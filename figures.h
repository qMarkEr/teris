#ifndef TETRIS_FIGURES_H
#define TETRIS_FIGURES_H
#define BLOCKS 4
#define TYPES "IJLOSTZ"
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
} fld;

void clear_layer(fld* f);

fld *init();

void fld_delete(fld *game);

void fig_delete(fig *f);

void spawn(fig *figure);

fig *figure(char name);

int collision(pnt f, fld field);

#endif //TETRIS_FIGURES_H
