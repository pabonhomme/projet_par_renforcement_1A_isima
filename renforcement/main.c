#include "game.h"

int main()
{
	SDL_Window* window; // fenetre de jeu
	SDL_Renderer* renderer; 
	SDL_Texture* character_texture;    
	SDL_Rect positionCharac = {0};
	SDL_Event event;
	int running = 1, teleport = 0, hasTeleported = 0;

	SDL_Rect source = {0},
			 destination = {0},                    // Rectangle définissant la zone de la texture à récupérer
           	 state = {0};                     // Rectangle de la vignette en cours dans la planche 

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

    character_texture = IMG_LoadTexture(renderer,"./img/george.png");
    
  	if (character_texture == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());

  	SDL_QueryTexture(character_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image
	int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 1;                        // zoom, car ces images sont un peu petites
    int largeurVignette = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        hauteurVignette = source.h / nb_images;   // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 0 * largeurVignette ;                          // La première vignette est en début de ligne
       state.y = 0 * hauteurVignette;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = largeurVignette;                    // Largeur de la vignette
       state.h = hauteurVignette;                    // Hauteur de la vignette

       destination.w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       destination.h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran

       destination.x = 300;
       destination.y = 300;

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
        	if(zoom >= 0)
        	{
        		state.x += largeurVignette;                // La première vignette est en début de ligne
        		state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
        		destination.w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       			destination.h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran
        		SDL_RenderCopy(renderer, character_texture, &state, &destination);    // Préparation de l'affichage  
        		destination.x = destination.x +  (largeurVignette * 0.05); // pour qu'il reste centré quand il diminue
       			destination.y = destination.y +  (hauteurVignette * 0.05);
        		zoom = zoom - 0.1;
        	}
        	else
        	{
        		teleport = 0;
				hasTeleported = 1;
				printf("zebi2\n");
				destination.x = 60;
       			destination.y = 60;
        	}        	
        }
        else if(hasTeleported)
        {
        	if(zoom <= 1)
        	{
        		state.x += largeurVignette;                // La première vignette est en début de ligne
        		state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
        		destination.w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       			destination.h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran
        		SDL_RenderCopy(renderer, character_texture, &state, &destination);     // Préparation de l'affichage  
        		destination.x = destination.x -  (largeurVignette * 0.05); // pour qu'il reste centré quand il diminue
       			destination.y = destination.y -  (hauteurVignette * 0.05);
        		zoom = zoom + 0.1;
        	}
        	else
        	{
        		hasTeleported = 0;
        	}
        }
        else
        {
        	// state.x = 0 * largeurVignette;                // La première vignette est en début de ligne
        	SDL_RenderCopy(renderer, character_texture,     // Préparation de l'affichage  
                    &state,
                    &destination); 
        }
        SDL_RenderPresent(renderer);
		SDL_Delay(100);
		SDL_RenderClear(renderer);
      
    }
}