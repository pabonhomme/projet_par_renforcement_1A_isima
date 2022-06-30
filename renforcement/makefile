CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf
EXEC=game

all: $(EXEC)

game: main.o menu.o game.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./game"

main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)

menu.o: menu.c
	$(CC) -o $@ -c $< $(CFLAGS)

game.o: game.c game.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
