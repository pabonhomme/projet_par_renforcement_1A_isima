#include <SDL2/SDL.h>
#include <stdio.h>
#include<string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

#define NB_TELEPORTER 20

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

void display_charac(SDL_Texture* character_texture, SDL_Renderer* renderer);
void teleport_to(SDL_Texture* character_texture, SDL_Renderer* renderer);

