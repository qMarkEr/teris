CC=gcc
SOURCE=main.c controls.c render.c figures.c
OUTPUT=built/tetris

all : build

build : $(SOURCE)
	$(CC) $(SOURCE) -lncurses -o $(OUTPUT)
