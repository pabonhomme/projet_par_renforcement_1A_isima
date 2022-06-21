#include <SDL2/SDL.h>
#include <stdio.h>

void clear(SDL_Renderer* renderer) {                                 // Je pense que vous allez faire moins laid :)

	SDL_SetRenderDrawColor(renderer,                                                
                         0, 0, 0,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void draw(SDL_Renderer* renderer, SDL_Rect *rectangle, int i) {                                 // Je pense que vous allez faire moins laid :)

	SDL_SetRenderDrawColor(renderer,                                                
                         (35*i)%255, (5*i)%255, (75*i)%255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);
	
	SDL_RenderFillRect(renderer, rectangle);
	SDL_RenderPresent(renderer);
}

void gameLoop(SDL_Renderer* renderer, SDL_Rect *rectangle)
{
	SDL_bool program_on = SDL_TRUE;             
	SDL_Event event; 
	int i = 0;                     

	while (program_on==SDL_TRUE)
	{                        

  		if (SDL_PollEvent(&event))
  		{                 
                                         
    		switch(event.type)
    		{                       
    			case SDL_QUIT :                           
      				program_on = SDL_FALSE;                
      				break;
      			case SDL_KEYDOWN:
    				switch (event.key.keysym.sym)
    				{             
      					case SDLK_LEFT: 
      						                     
        					break;
      					case SDLK_RIGHT: 
      						break;
      					case SDLK_UP:                               
        					                                         
        					break;
        				default:                              
      						break;
      				}
    			default:                      
      				break;
    		}
  		}
  		clear(renderer);
  		draw(renderer, rectangle, i);
  		i++;
  		SDL_Delay(100);
 	}
}


int main() 
{
  SDL_Window *window;
  SDL_Renderer *renderer; 
  SDL_Rect rectangle;                    // Future fenêtre de droite
  int statut = EXIT_FAILURE;

  SDL_DisplayMode screen;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    SDL_Log("Error : SDL initialisation - %s\n", 
    SDL_GetError());                // l'initialisation de la SDL a échoué 
    goto Quit;
  }

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                            screen.h * 0.66,
                            SDL_WINDOW_OPENGL);
  if (window == NULL)
  {
  	SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());                 // échec de la création de la fenêtre
  	goto Quit;
  }
  		
  /* Création du renderer */
  renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
  {
  	fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
 	goto Quit;
  }

  rectangle.x = 0;                                                  // x haut gauche du rectangle
  rectangle.y = 0;                                                  // y haut gauche du rectangle
  rectangle.w = 50;                                                // sa largeur (w = width)
  rectangle.h = 50;                                                // sa hauteur (h = height)

  gameLoop(renderer, &rectangle);                                     
                       
  SDL_Delay(1000);                                     

Quit: 
	if(NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if(NULL != window)
		SDL_DestroyWindow(window);
  	SDL_Quit();
  	return statut;

return 0;
}