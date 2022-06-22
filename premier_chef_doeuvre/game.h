#include <SDL2/SDL.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

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