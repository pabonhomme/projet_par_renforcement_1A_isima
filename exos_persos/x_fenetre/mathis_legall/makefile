CC=gcc
CFLAGS=-Wextra -Wall
LDFLAGS=-lSDL2
EXEC=xfenetre

all:$(EXEC)

xfenetre: xfenetre.o
	$(CC) -o xfenetre xfenetre.o -lSDL2
	@echo "Lancer le programme avec ./xfenetre"

xfenetre.o: xfenetre.c
			$(CC) -o xfenetre.o -c xfenetre.c -lSDL2

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)