CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=-lSDL2 -lSDL2_ttf
EXEC=lifeGame

all: $(EXEC)

lifeGame: lifegame.o game.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./sprite"

lifegame.o: lifegame.c
	$(CC) -o $@ -c $< $(CFLAGS)

game.o: game.c game.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
