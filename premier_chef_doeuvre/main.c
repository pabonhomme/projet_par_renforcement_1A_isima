#include "game.h"


int main()
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface *tmp;
	SDL_Surface *tmp2;
	SDL_Texture* character;
	Enemies_t enemies[NB_ENEMIES_MAX];
	SDL_Rect positionCharac = {0};
	SDL_Event event;
	int colorkey;
	int animFlipC = 0;
	int running = 1;
	int currDirection = DIR_RIGHT;
	int nextDirection;
	int markov[4][10] = { {0,0,0,0,0,0,0,1,2,3},

						 {0,0,0,1,1,1,2,2,2,3},

						 {0,1,2,2,2,2,2,2,2,3},

						 {0,0,1,1,2,2,3,3,3,3} };

	window = SDL_CreateWindow("Premier chef d'oeuvre",	
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT,
							  SDL_WINDOW_RESIZABLE);
	if (window == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }

	tmp = SDL_LoadBMP("sprite.bmp");
	tmp2 = SDL_LoadBMP("sprite.bmp");

	//colorkey = SDL_MapRGB((window->icon)->format,255, 0, 255);
	//SDL_SetColorKey(tmp, SDL_TRUE, colorkey);
	character = SDL_CreateTextureFromSurface(renderer,tmp);
	initEnemies(enemies,SDL_CreateTextureFromSurface(renderer,tmp));

    positionCharac.x = (SCREEN_WIDTH - SPRITE_SIZE) / 2;
    positionCharac.y = (SCREEN_HEIGHT - SPRITE_SIZE) / 2;

    while(running)
    {
    	while (SDL_PollEvent(&event))
    	{
    		handleEvent(event,&running,&currDirection,&animFlipC,&positionCharac);
    	}

		moveCharacter(character,renderer,positionCharac,currDirection,animFlipC);
		SDL_Delay(1);
		moveEnemies(enemies,renderer,6,markov);
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
		SDL_RenderClear(renderer);
    }

	return 0;
}
