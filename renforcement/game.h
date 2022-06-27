#include <SDL2/SDL.h>
#include <stdio.h>
#include<string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Taille de la fenêtre */
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

void display_charac(SDL_Texture* character_texture, SDL_Renderer* renderer);
void teleport_to(SDL_Texture* character_texture, SDL_Renderer* renderer);

