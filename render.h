#ifndef TETRIS_RENDER_H
#define TETRIS_RENDER_H

#include "figures.h"

void menu(char* menu);

void render(fld *field);

void game_output(fld *f);

void fig_output(fig *f, int stop);

void next_fig(fld* f, char name, int stop);

#endif //TETRIS_RENDER_H
