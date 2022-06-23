#include "game.h"

int main()
{
    SDL_Rect rect_score;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface *tmp;
	SDL_Surface *tmp2;
	SDL_Texture* character;                          
    SDL_Texture* diamond_texture;  
    SDL_Texture* bg_texture;  
    SDL_Texture *score_texture;
	Enemies_t enemies[NB_ENEMIES_MAX];
	SDL_Rect positionCharac = {0};
	SDL_Event event;
	int colorkey,
        score =0,
		nb_enemies = 1,
	 	animFlipC = 0,
	 	running = 1,
	 	currDirection = DIR_RIGHT,
		hasIntersectDiamond = 0, 
		diamondLine = rand()%2, 
		diamondColumn = rand()%3, 
		destination_x = rand()%SCREEN_WIDTH, 
		destination_y = rand()%SCREEN_HEIGHT,
		markov[4][10] = { {0,0,0,0,0,0,0,1,2,3},

						 {0,0,0,1,1,1,2,2,2,3},

						 {0,1,2,2,2,2,2,2,2,3},

						 {0,0,1,1,2,2,3,3,3,3} };
    char mot[100];
    char texte[100];
    strcpy(texte, "Score: ");
    sprintf(mot,"%d",score); 
    strcat(texte,mot);

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

	window = SDL_CreateWindow("Premier chef d'oeuvre",	
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT,
							  SDL_WINDOW_RESIZABLE);
	if (window == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
	}

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());

        // faire ce qu'il faut pour quitter proprement
    }
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./font/SIXTY.TTF", 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text(renderer, 0, 0, texte,  font, &score_texture, &rect_score);
    

  	bg_texture = IMG_LoadTexture(renderer,"./img/background.png");
  	if (bg_texture == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());  

    diamond_texture = IMG_LoadTexture(renderer,"./img/listDiamond.png");
    create_diamond(diamond_texture, renderer, diamondLine, diamondColumn, destination_x, destination_y );
  
  	if (diamond_texture == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());

	tmp = SDL_LoadBMP("./img/character.bmp");
	tmp2 = SDL_LoadBMP("./img/enemy.bmp");
	colorkey = SDL_MapRGB(tmp->format,255, 0, 255); // on enlève le background du sprite
	SDL_SetColorKey(tmp, SDL_TRUE, colorkey);
	SDL_SetColorKey(tmp2, SDL_TRUE, colorkey);
	character = SDL_CreateTextureFromSurface(renderer,tmp);
	initEnemies(enemies,SDL_CreateTextureFromSurface(renderer,tmp2));

    positionCharac.x = (SCREEN_WIDTH - SPRITE_SIZE) / 2;
    positionCharac.y = (SCREEN_HEIGHT - SPRITE_SIZE) / 2;

    while(running)
    {
    	while (SDL_PollEvent(&event))
    	{
    		handleEvent(event,&running,&currDirection,&animFlipC,&positionCharac, &nb_enemies);
    	}
        SDL_RenderClear(renderer);
        display_background(bg_texture,window,renderer);
        SDL_RenderCopy(renderer, score_texture, NULL, &rect_score);
        score++;
        sprintf(mot,"%d",score);
        strcpy(texte, "");
        strcpy(texte, "Score: ");
        strcat(texte,mot);
        get_text(renderer, 0, 0, texte,  font, &score_texture, &rect_score);

    	if(hasIntersectDiamond)
        {
        	diamondLine = rand()%2, 
			diamondColumn = rand()%3, 
			destination_x = rand()%SCREEN_WIDTH, 
			destination_y = rand()%SCREEN_HEIGHT;
        	create_diamond(diamond_texture, renderer, diamondLine, diamondColumn, destination_x, destination_y );
        	hasIntersectDiamond = 0;

        }
        else
        {
        	create_diamond(diamond_texture, renderer, diamondLine, diamondColumn, destination_x, destination_y );
        }

		moveCharacter(character,renderer,positionCharac,currDirection,animFlipC);
		moveEnemies(enemies,renderer,nb_enemies,markov);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
		SDL_RenderClear(renderer);
    }

    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(diamond_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
	return 0;
}
