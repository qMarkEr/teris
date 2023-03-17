#ifndef TETRIS_GAME_STATE_H
#define TETRIS_GAME_STATE_H
#include "figures.h"

int add_figure(fld *field, fig f);

void score(fld* f, int count);

void clear_layer(fld* f);
#endif //TETRIS_GAME_STATE_H
