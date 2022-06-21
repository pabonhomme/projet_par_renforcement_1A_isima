CC=gcc
CFLAGS=-Wextra -Wall -lm
LDFLAGS=-lSDL2
EXEC=exo2

all:$(EXEC)

exo2: exo2.o
	$(CC) -o exo2 exo2.o -lSDL2 -lm
	@echo "Lancer le programme avec ./exo2"

exo2.o: exo2.c
			$(CC) -o exo2.o -c exo2.c -lSDL2 -lm

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)