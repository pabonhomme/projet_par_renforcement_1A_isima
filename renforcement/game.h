#include <SDL2/SDL.h>
#include <stdio.h>
#include<string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

/* Pas du sprite */
#define SPRITE_STEP 4

/* Direction du sprite */
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

/* Structures */
typedef struct character
{
	SDL_Texture* sprite;
	SDL_Rect position;
	SDL_Rect state;
	int row;
	int column;

} Character_t;

typedef struct teleporter
{
	int positionRow;
	int positionColumn;
	int destinationRow;
	int destinationColumn;

} Teleporter_t;