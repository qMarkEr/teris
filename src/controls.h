#ifndef TETRIS_CONTROLS_H
#define TETRIS_CONTROLS_H

#include "figures.h"

void shift(fld *f, int direction);

void rotate(fld *f);

void move_down(fld* f, int* stop);

void move_fig(fld *field, int *stop);

#endif //TETRIS_CONTROLS_H
