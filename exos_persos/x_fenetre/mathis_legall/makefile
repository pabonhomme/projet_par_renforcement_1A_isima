CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=-lSDL2
EXEC=x_fenetre

all:$(EXEC)

x_fenetre: xfenetre.o
	$(CC) -o xfenetre xfenetre.o -lSDL2
	@echo "Lancer le programme avec ./x_fenetre"

xfenetre.o: xfenetre.c
			$(CC) -o xfenetre.o -c xfenetre.c -lSDL2

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
