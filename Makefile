CC=gcc
SOURCE=src/main.c src/controls.c src/render.c src/figures.c src/game_state.c
OUTPUT=built/tetris

all : build

build : $(SOURCE)
	$(CC) $(SOURCE) -lncurses -o $(OUTPUT)
