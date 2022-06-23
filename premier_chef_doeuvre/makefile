CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=-lSDL2 -lSDL_image -lSDL2_ttf
EXEC=game

all: $(EXEC)

game: main.o game.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./sprite"

main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)

game.o: game.c game.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
