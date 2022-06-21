CC=gcc
CFLAGS=-Wextra -Wall 
LDFLAGS=-lSDL2
EXEC=snake

all: $(EXEC)

snake: snake.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\nLancer le programme avec ./snake"

snake.o: snake.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -rf *.o

rmExec: clean
	rm -rf $(EXEC)
