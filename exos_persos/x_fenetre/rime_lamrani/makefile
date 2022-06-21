CC=gcc
CFLAGS=-Wextra -Wall 
LDFLAGS=-lSDL2
EXEC=xfen

all: $(EXEC)

xfen: xfen.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./xfen"

xfen.o: xfen.c
	$(CC) -o $@ -c $< $(sdl2-config --cflags --libs) $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
