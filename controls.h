#ifndef TETRIS_CONTROLS_H
#define TETRIS_CONTROLS_H

#include "figures.h"

void shift(fld* f, int direction, fig *prev);
void rotate(fld* f, fig *prev);

#endif //TETRIS_CONTROLS_H
