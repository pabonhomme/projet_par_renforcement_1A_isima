#include <SDL2/SDL.h>
#include <stdio.h>
#include<string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

/* Taille d'un sprite */
#define SPRITE_SIZE 50

/* Le sprite contient 2 images pour chaque position
Ordre de chaque position dans le sprite */
#define DIR_UP          0
#define DIR_RIGHT       1
#define DIR_DOWN        2
#define DIR_LEFT        3

/* Nombre de pixels pour chaque pas du personnage */
#define SPRITE_STEP 5

#define NB_ENEMIES_MAX 50

void display_background(SDL_Texture *bg_texture, SDL_Window *window,
                         SDL_Renderer *renderer);
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);

typedef struct enemies
{
	SDL_Texture* sprite;
	SDL_Rect position;
	int prevDirection;
	int animFlip;

} Enemies_t;

void handleEvent(SDL_Event event, int *running, int *currDirection, int* animFlip, SDL_Rect* position, int* nb_enemies);
void initEnemies(Enemies_t enemies[], SDL_Texture* enemy);
void moveCharacter(SDL_Texture* sprite, SDL_Renderer* renderer, SDL_Rect position, int currDirection, int animFlip);
int newDirection(int markov[][10], int prevDirection);
void moveEnemies(Enemies_t enemies[], SDL_Renderer* renderer, int nb_enemies, int markov[][10]);


void create_diamond(SDL_Texture* diamond_texture, SDL_Renderer* renderer, 
	int diamondLine, int diamondColumn, int destination_x, int destination_y );

