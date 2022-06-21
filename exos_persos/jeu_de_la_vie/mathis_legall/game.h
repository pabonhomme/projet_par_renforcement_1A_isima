#include <stdio.h>
#include <stdlib.h>

int** mallocGrid(int n);
void initGrid(int n, int** grid);
void printGrid(int n, int** grid);
void newCell(int n, int i, int j, int** grid, int** copyGrid, int birth[], int survive[]);
void newGrid(int n, int** grid, int** copyGrid, int birth[], int survive[]);
void freeGrid(int n, int** grid);
