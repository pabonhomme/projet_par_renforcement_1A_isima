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


int hasToTeleport(Teleporter_t tabTeleporter[], Character_t character);
void initTeleporter(Teleporter_t tabTeleporter[]);
void get_text(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);
void display_background(SDL_Texture *bg_texture, SDL_Window *window,SDL_Renderer *renderer);