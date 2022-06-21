#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159

void RotateTriangle(SDL_Point point[], double theta, int xG, int yG)
{
	int i;
	theta *= PI / 180;

	for (i=0; i<4; i++)
	{
		point[i].x = (point[i].x-xG)*cos(theta)+(point[i].y-yG)*sin(theta)+xG;
		point[i].y = -1*(point[i].x-xG)*sin(theta)+(point[i].y-yG)*cos(theta)+yG;
	}
}

int main()
{
	int i = 0;
	SDL_Renderer *renderer;
	SDL_Event event;
	SDL_bool program_on = SDL_TRUE; 
	
	SDL_Point point[4];
	point[0].x = 500;
	point[0].y = 100;
	point[1].x = 300;
	point[1].y = 600;
	point[2].x = 700;
	point[2].y = 500;
	point[3].x = 500;
	point[3].y = 100;

	int xG = 600;
	int yG = 400;

	double theta = PI;


	SDL_Window *window = SDL_CreateWindow(
		"Window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1000, 1000,
		SDL_WINDOW_RESIZABLE);

	if (window == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

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
  		SDL_SetRenderDrawColor(renderer, (35*i)%255, (5*i)%255, (75*i)%255, 255);
  		RotateTriangle(point,theta,xG,yG);
  		SDL_RenderDrawLines(renderer, point, 4);
  		SDL_RenderPresent(renderer);
  		SDL_Delay(100);

  		i+=1;
	}

	return 0;
		
}