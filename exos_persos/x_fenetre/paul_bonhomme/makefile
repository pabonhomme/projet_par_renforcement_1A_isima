CC=gcc
CFLAGS=-Wextra -Wall 
LDFLAGS=-lSDL2
EXEC=x_fenetre

all: $(EXEC)

x_fenetre: x_fenetre.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./x_fenetre"

x_fenetre.o: x_fenetre.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)