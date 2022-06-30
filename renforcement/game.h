#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

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
#define DIRECTION 4

/* Structures */
#define NB_TELEPORTER 22
#define NB_STATE 529
#define NB_ITE 200

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

typedef struct stateList
{
	int state;
	int action;
	int reward;

} StateList_t;


int hasToTeleport(Teleporter_t tabTeleporter[], Character_t character);
void initTeleporter(Teleporter_t tabTeleporter[]);
float maxStateQtable(float qtable[][DIRECTION], int state, int *argmax);
void initQtable(float qTable[][DIRECTION]);
void updateQtable(float qTable[][DIRECTION], StateList_t stateList[], int nbState, float xi, float gamma);
void printQtable(float qTable[][DIRECTION]);
void printStateList(StateList_t stateList[], int nbState);
void sauvegarder(char* nomFichier, float grid[][DIRECTION]);
void charger(char* nomFichier,float grid[][DIRECTION]);
void initStateList(StateList_t stateList[]);
void generation(); 
void game_ia();