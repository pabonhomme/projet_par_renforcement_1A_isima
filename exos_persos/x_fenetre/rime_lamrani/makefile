CC=gcc
CFLAGS=-Wextra -Wall 
LDFLAGS=-lSDL2
EXEC=x_fenetre

all: $(EXEC)

x_fenetre: xfen.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./x_fenetre"

xfen.o: xfen.c
	$(CC) -o $@ -c $< $(sdl2-config --cflags --libs) $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
