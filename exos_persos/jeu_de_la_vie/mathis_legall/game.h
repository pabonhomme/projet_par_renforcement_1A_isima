#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#define SIZECELL 50 
#define SIZEWINDOW 600
#define SIZEGRID SIZEWINDOW/SIZECELL

//MENU
void display_background(SDL_Texture *bg_texture, SDL_Window *window,
                         SDL_Renderer *renderer);
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);
int menu(int *running);

//GAME
void displayRects(SDL_Rect rect, SDL_Renderer *renderer, int** grid);
int** mallocGrid(int n);
void initGrid(int n, int** grid);
void printGrid(int n, int** grid);
void newCell(int n, int i, int j, int** grid, int** copyGrid, int birth[], int survive[]);
void newGrid(int n, int** grid, int** copyGrid, int birth[], int survive[]);
void freeGrid(int n, int** grid);
void newCellToric(int n, int i, int j, int** grid, int** copyGrid, int birth[], int survive[]);
void newGridToric(int n, int** grid, int** copyGrid, int birth[], int survive[]);
int equalGrid(int n, int** grid1, int** grid2);