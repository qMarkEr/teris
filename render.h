#ifndef TETRIS_RENDER_H
#define TETRIS_RENDER_H

#include "figures.h"

#define WIDTH 10
#define HEIGHT 20

void game_output(fld *f);

void fig_output(fig *f, int stop);

void render(fld *field);

void menu(char* menu);

void next_fig(fld* f, char name, int stop);

#endif //TETRIS_RENDER_H
