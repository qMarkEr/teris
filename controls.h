#ifndef TETRIS_CONTROLS_H
#define TETRIS_CONTROLS_H

#include "figures.h"

void shift(fld *f, int direction, fig *prev);

void rotate(fld *f, fig *prev);

void move_down(fld* f, fig *prev, int* stop);

void move_fig(fld *field, fig* f, int *stop);

#endif //TETRIS_CONTROLS_H
