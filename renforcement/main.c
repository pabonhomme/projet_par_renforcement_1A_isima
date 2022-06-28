#include "game.h"

int main()
{
	SDL_Window* window; // fenetre de jeu
	SDL_Renderer* renderer; 
	SDL_Event event;
	int running = 1, teleport = 0, hasTeleported = 0;
	Character_t character;
	// Teleporter_t tabTeleporter[NB_TELEPORTER], 
	// t1 = {positionRow = 3, positionColumn = 2, destinationRow = 17, destinationColumn = 7},
	// t2 = {positionRow = 17, positionColumn = 7, destinationRow = 3, destinationColumn = 2};

	// tabTeleporter[0] = t1;
	// tabTeleporter[1] = t2;

	SDL_Rect source = {0};

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

    character.sprite = IMG_LoadTexture(renderer,"./img/george.png");
    
  	if (character.sprite == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());

  	SDL_QueryTexture(character.sprite, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image
	int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 0.8;                        // zoom, car ces images sont un peu petites
    int offset_w = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_h = source.h / nb_images;   // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       (character.state).x = 2 * offset_w ;                          // La première vignette est en début de ligne
       (character.state).y = 2 * offset_h;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       (character.state).w = offset_w;                    // Largeur de la vignette
       (character.state).h = offset_h;                    // Hauteur de la vignette

       (character.position).w = offset_w * zoom;       // Largeur du sprite à l'écran
       (character.position).h = offset_h * zoom;       // Hauteur du sprite à l'écran

       (character.position).x = 300;
       (character.position).y = 300;

	while (running)
    {
			while (SDL_PollEvent(&event))
        	{	
            	switch (event.type)
            	{
            		case SDL_WINDOWEVENT:
                		printf("window event\n");
                		switch (event.window.event)
                		{
                			case SDL_WINDOWEVENT_CLOSE:
                    			printf("appui sur la croix\n");
                    			break;
                			default:
                				break;
                		}
                		break;
            		case SDL_QUIT:
                		printf("on quitte\n");
                		running = 0;
                		break;
                	case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								running = 0;
								break;
							case SDLK_SPACE:
								teleport = 1;
								break;
							default:
								break;
						}
						break;
					default:
						break;
            	}
        	}
        if(teleport)
        {
        	if(zoom > 0)
        	{
        		(character.state).x += offset_w;                // La première vignette est en début de ligne
        		(character.state).x %= source.w;                 // La vignette qui suit celle de fin de ligne est
        		(character.position).w = offset_w * zoom;       // Largeur du sprite à l'écran
       			(character.position).h = offset_h * zoom;       // Hauteur du sprite à l'écran 
        		(character.position).x = (character.position).x +  (offset_w * 0.05); // pour qu'il reste centré quand il diminue
       			(character.position).y = (character.position).y +  (offset_h * 0.05);
        		zoom = zoom - 0.1;
        	}
        	else
        	{
        		teleport = 0;
				hasTeleported = 1;
				(character.position).x = 60;
       			(character.position).y = 60;
        	}        	
        }
        else if(hasTeleported)
        {
        	if(zoom < 0.8)
        	{
        		printf("zoom : %f\n",zoom );
        		(character.state).x += offset_w;                // La première vignette est en début de ligne
        		(character.state).x %= source.w;                 // La vignette qui suit celle de fin de ligne est
        		(character.position).w = offset_w * zoom;       // Largeur du sprite à l'écran
       			(character.position).h = offset_h * zoom;       // Hauteur du sprite à l'écran
        		(character.position).x = (character.position).x -  (offset_w * 0.05); // pour qu'il reste centré quand il diminue
       			(character.position).y = (character.position).y -  (offset_h * 0.05);
        		zoom = zoom + 0.1;
        	}
        	else
        	{
        		hasTeleported = 0;
        	}
        }
        SDL_RenderCopy(renderer, character.sprite, &character.state, &character.position);      // Préparation de l'affichage  
        SDL_RenderPresent(renderer);
		SDL_Delay(100);
		SDL_RenderClear(renderer);
      
    }
}