#include <SDL2/SDL.h>
#include <stdio.h>
#include<string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

typedef struct character
{
	SDL_Texture* sprite;
	SDL_Rect position;

} Character_t;

typedef struct teleporter
{
	int positionX;
	int positionY;
	int destinationX;
	int destinationY;
	
} Teleporter_t;