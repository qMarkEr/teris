#ifndef TETRIS_RENDER_H
#define TETRIS_RENDER_H

#include "figures.h"

#define WIDTH 10
#define HEIGHT 20

void fld_output(int **frame);

void fig_output(fld field, fig f, int stop);

void move_down(fld* f, fig *prev, int* stop);

void render(fld *field);


#endif //TETRIS_RENDER_H
