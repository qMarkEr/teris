#ifndef TETRIS_RENDER_H
#define TETRIS_RENDER_H

#include "figures.h"

#define WIDTH 10
#define HEIGHT 20

void game_output(fld *f);

void fig_output(fig *f, int stop);

void render(fld *field);


#endif //TETRIS_RENDER_H
