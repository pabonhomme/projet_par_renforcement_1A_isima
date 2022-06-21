#include <SDL2/SDL.h>
#include <stdio.h>

#define SIZE 18

void CreateWindow(SDL_Window* TabWindow[])
{
	int i;
	int j;
	SDL_Window* window;

	for (i=1; i<=SIZE/2; i++)
	{
		window = SDL_CreateWindow(
			"Window",
			i*50, i*50,
			100, 100,
			SDL_WINDOW_RESIZABLE);

		if (window == 0)
		{
			fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
		}

		TabWindow[i-1] = window;
	}

	for (j=1; j<=SIZE/2; j++)
	{
		window = SDL_CreateWindow(
			"Window",
			500+j*50, 500-j*50,
			100, 100,
			SDL_WINDOW_RESIZABLE);

		if (window == 0)
		{
			fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
		}

		TabWindow[j+SIZE/2] = window;
	}
}

void CloseWindow(SDL_Window* TabWindow[])
{
	int i;

	for (i=0; i<SIZE; i++)
	{
		SDL_DestroyWindow(TabWindow[i]);
	}
}

void MoveWindowRight(SDL_Window* TabWindow[], int *sens)
{
	int i = 0;
	int x,y, xmax, ymax;
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	while (i<=SIZE && *sens == 0)
	{	
		SDL_GetWindowPosition(TabWindow[SIZE-1], &xmax, &ymax);
		if (xmax+210 < current.w)
		{
			SDL_GetWindowPosition(TabWindow[i], &x, &y);
			SDL_SetWindowPosition(TabWindow[i], x+10, y);
		}
		else
		{
			*sens = 1;
		}
		i = i+1;
	}
}

void MoveWindowLeft(SDL_Window* TabWindow[], int *sens)
{
	int i = 0;
	int x,y, xmin, ymin;
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	while (i<=SIZE && *sens == 1)
	{	
		SDL_GetWindowPosition(TabWindow[0], &xmin, &ymin);
		if (xmin-210 > 0)
		{
			SDL_GetWindowPosition(TabWindow[i], &x, &y);
			SDL_SetWindowPosition(TabWindow[i], x-10, y);
		}
		else
		{
			*sens = 0;
		}
		i = i+1;
	}
}

int main()
{
	SDL_Window* TabWindow[SIZE];
	SDL_bool program_on = SDL_TRUE;              
	SDL_Event event; 
	int sens = 0;

	CreateWindow(TabWindow);

	while (program_on == SDL_TRUE)
	{                           
		if (SDL_PollEvent(&event))
		{                
            switch(event.type)
            {                      
    		case SDL_QUIT:                          
      			program_on = SDL_FALSE;                 
      			break;

      		case SDL_KEYDOWN:
      			switch (event.key.keysym.sym)
      			{
      				case SDLK_SPACE:
      					program_on = SDL_FALSE;
      					break;
      			}

    		default:                                 
		     	break;
    		}
  		}
  		
  		if (sens == 0)
  		{
  			MoveWindowRight(TabWindow,&sens);
  		}
 		else
 		{
 			MoveWindowLeft(TabWindow,&sens);
 		}
 		SDL_Delay(50);
 	}
	CloseWindow(TabWindow);
}