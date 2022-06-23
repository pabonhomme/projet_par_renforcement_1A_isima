CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=-lSDL2 -lSDL2_image
EXEC=sprite

all: $(EXEC)

sprite: sprite.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./sprite"

sprite.o: sprite.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
