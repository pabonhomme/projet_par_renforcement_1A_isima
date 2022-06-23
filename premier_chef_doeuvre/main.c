#include "game.h"


int main()
{
	int running = 1, 
		nbDiamond = 0, 
		hasIntersect = 0, 
		diamondLine = rand()%2, 
		diamondColumn = rand()%3, 
		destination_x = rand()%SCREEN_WIDTH, 
		destination_y = rand()%SCREEN_HEIGHT;
	SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;    
                           
    SDL_Texture* diamond_texture;                                                                

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Premier chef d'oeuvre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        // on peut aussi utiliser SLD_Log()
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        // faire ce qu'il faut pour quitter proprement
    }

    diamond_texture = IMG_LoadTexture(renderer,"./img/listDiamond.png");
    create_diamond(diamond_texture, nbDiamond, window, renderer, diamondLine, diamondColumn, destination_x, destination_y );
    nbDiamond++;
  
  	if (diamond_texture == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());

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
                	case SDL_KEYDOWN:
            			switch (event.key.keysym.sym)
            			{
              				case SDLK_SPACE:
                				hasIntersect = 1;
                				break;
                		}
                		break;
            		case SDL_QUIT:
                		printf("on quitte\n");
                		running = 0;
                		break;
            	}
        	}
        if(hasIntersect)
        {
        	diamondLine = rand()%2, 
			diamondColumn = rand()%3, 
			destination_x = rand()%SCREEN_WIDTH, 
			destination_y = rand()%SCREEN_HEIGHT;
        	create_diamond(diamond_texture, nbDiamond, window, renderer, diamondLine, diamondColumn, destination_x, destination_y );
        	hasIntersect = 0;

        }
        else
        {
        	create_diamond(diamond_texture, nbDiamond, window, renderer, diamondLine, diamondColumn, destination_x, destination_y );
        }
        
     SDL_RenderPresent(renderer);             
     SDL_Delay(1000);                         
     SDL_RenderClear(renderer);               // Effacer la fenêtre
      
    }
    
    SDL_DestroyTexture(diamond_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}