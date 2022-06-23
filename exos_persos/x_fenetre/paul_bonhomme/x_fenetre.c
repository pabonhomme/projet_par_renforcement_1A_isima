#include <SDL2/SDL.h>
#include <stdio.h>

#define SIZE 22

int sens = 0;

void createWindows(SDL_Window *tabWindows[])
{
	int i,j = 0;
	SDL_Window *window = NULL;
	for(i=0;i<SIZE/2;i++)
	{
		window = SDL_CreateWindow(
      		"Window",                    // codage en utf8, donc accents possibles
      		i*50, i*50,                                  // coin haut gauche en haut gauche de l'écran
      		200, 200,                              // largeur = 400, hauteur = 300
      		SDL_WINDOW_RESIZABLE);
		if (window == NULL) 
		{
    		SDL_Log("Error : SDL window 1 creation - %s\n", 
    		SDL_GetError());                 // échec de la création de la fenêtre
  			
    	} 
		tabWindows[i] = window;
	}
	for(j=0;j<SIZE/2;j++)
	{
		window = SDL_CreateWindow(
      		"Window",                    // codage en utf8, donc accents possibles
      		j*50, 500-j*50,                                  // coin haut gauche en haut gauche de l'écran
      		200, 200,                              // largeur = 400, hauteur = 300
      		SDL_WINDOW_RESIZABLE);
		if (window == NULL) 
		{
    		SDL_Log("Error : SDL window 1 creation - %s\n", 
    		SDL_GetError());                 // échec de la création de la fenêtre
  			
    	} 
		tabWindows[i] = window;
		i++;
	}

}

void closeWindows(SDL_Window *tabWindows[])
{
	int i = 0;
	for(i =0; i<SIZE; i++)
	{
		SDL_DestroyWindow(tabWindows[i]);
	}

}

void moveWindowsRight(SDL_Window *tabWindows[])
{
	SDL_DisplayMode current;
	int i, x, y, xmax, ymax= 0;
	SDL_GetCurrentDisplayMode(0, &current);

	while(i < SIZE && sens == 0)
	{
		SDL_GetWindowPosition(tabWindows[SIZE-1], &xmax, &ymax);
		if((xmax+250)< current.w)
		{
			SDL_GetWindowPosition(tabWindows[i], &x, &y);
			SDL_SetWindowPosition(tabWindows[i], x+50, y);
		}
		else 
			sens = 1;
		i++;
	}
}

void moveWindowsLeft(SDL_Window *tabWindows[])
{
	SDL_DisplayMode current;
	int i, x, y, xmin, ymin= 0;
	SDL_GetCurrentDisplayMode(0, &current);

	while(i < SIZE && sens == 1)
	{
		SDL_GetWindowPosition(tabWindows[0], &xmin, &ymin);
		if((xmin-50)> 0)
		{
			SDL_GetWindowPosition(tabWindows[i], &x, &y);
			SDL_SetWindowPosition(tabWindows[i], x-50, y);
		}
		else sens = 0;
		i++;
	}
}

void gameLoop(SDL_Window *tabWindows[])
{
	SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
	SDL_Event event;                              // c'est le type IMPORTANT !!

	while (program_on==SDL_TRUE)
	{                           // Voilà la boucle des évènements 

  		if (SDL_PollEvent(&event))
  		{                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
                                              // de file dans 'event'
    		switch(event.type)
    		{                       // En fonction de la valeur du type de cet évènement
    			case SDL_QUIT :                           // Un évènement simple, on a cliqué sur la x de la fenêtre
      				program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
      				break;
    			case SDL_KEYDOWN:
    				switch (event.key.keysym.sym)
    				{             // la touche appuyée est ...
      					case SDLK_SPACE:                            // ou 'SPC'                        // basculement pause/unpause
        					break;
      					case SDLK_ESCAPE:  
      					case SDLK_q:                                // ou 'q'
        					program_on = SDL_FALSE;                         // 'escape' ou 'q', d'autres façons de quitter le programme                                     
        					break;
        				default:                                  // L'évènement défilé ne nous intéresse pas
      						break;
      				}
    			default:                                  // L'évènement défilé ne nous intéresse pas
      				break;
    		}
  		}
  // Affichages et calculs souvent ici
  		if(sens == 0)
  			moveWindowsRight(tabWindows);
  		else moveWindowsLeft(tabWindows);
  		SDL_Delay(100);
 	}
}

/************************************/
/*  exemple de création de fenêtres */
/************************************/
int main() 
{
  SDL_Window *tabWindows[SIZE];                    // Future fenêtre de droite
  int statut = EXIT_FAILURE;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    SDL_Log("Error : SDL initialisation - %s\n", 
    SDL_GetError());                // l'initialisation de la SDL a échoué 
    goto Quit;
  }

  createWindows(tabWindows);
  gameLoop(tabWindows);
  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(5000);                           // Pause exprimée  en ms
  closeWindows(tabWindows);

Quit: 
  	SDL_Quit();
  	return statut;

return 0;
}




