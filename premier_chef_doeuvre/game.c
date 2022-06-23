#include "game.h"

void handleEvent(SDL_Event event, int *running, int *currDirection, int* animFlip, SDL_Rect* position)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					*running = 0;
					break;

				case SDLK_UP:
					*currDirection = DIR_UP;
					*animFlip = 1 - *animFlip;
					position->y = ((position->y)-SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
					break;

				case SDLK_DOWN:
					*currDirection = DIR_DOWN;
					*animFlip = 1 - *animFlip;
					position->y = ((position->y)+SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
					break;

				case SDLK_LEFT:
					*currDirection = DIR_LEFT;
					*animFlip = 1 - *animFlip;
					position->x = ((position->x)-SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
					break;

				case SDLK_RIGHT:
					*currDirection = DIR_RIGHT;
					*animFlip = 1 - *animFlip;
					position->x = ((position->x)+SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}
}


void initEnemies(Enemies_t enemies[], SDL_Texture* enemy)
{
	int i;

	for (i=0; i<NB_ENEMIES_MAX; i++)
	{
		enemies[i].sprite = enemy;
		(enemies[i].position).x = rand()%SCREEN_WIDTH;
    	(enemies[i].position).y = rand()%SCREEN_HEIGHT;
    	enemies[i].prevDirection = rand()%4;
    	enemies[i].animFlip = 0;

	}
}

void moveCharacter(SDL_Texture* sprite, SDL_Renderer* renderer, SDL_Rect position, int currDirection, int animFlip)
{
	int nb_images = 8;
	int offset_x,offset_y;
	float zoom = 1.5;

	SDL_Rect 
            source = {0},                            
            destination = {0},              
            state = {0};  

    SDL_QueryTexture(sprite,NULL,NULL,&source.w, &source.h);

    offset_x = source.w/nb_images;
    offset_y = source.h;				  

    state.x = offset_x*(2*currDirection+animFlip);                          
    state.y = 0;                    
    state.w = offset_x;                    
    state.h = offset_y;  

    destination.w = offset_x*zoom;      
    destination.h = offset_y*zoom;       

    destination.x = position.x;
    destination.y = position.y; 

    SDL_RenderCopy(renderer, sprite, &state, &destination);  
}



int newDirection(int markov[][10], int prevDirection)
{
	int alpha = rand()%10;

	return (markov[prevDirection][alpha]);
}


void moveEnemies(Enemies_t enemies[], SDL_Renderer* renderer, int nb_enemies, int markov[][10])
{
	int nb_images = 8;
	int offset_x,offset_y;
	int i;
	int nextDirection;
	float zoom = 1.5;

	SDL_Rect 
            source = {0},                            
            destination = {0},              
            state = {0};  

    for (i=0; i<nb_enemies; i++)
    {	
	    SDL_QueryTexture(enemies[i].sprite,NULL,NULL,&source.w, &source.h);

	    offset_x = source.w/nb_images;
	    offset_y = source.h;				  

	    nextDirection = newDirection(markov,enemies[i].prevDirection);
	    if (enemies[i].prevDirection == nextDirection)
		{
			enemies[i].animFlip = 1 - enemies[i].animFlip;
		}

	    state.x = offset_x*(2*nextDirection+enemies[i].animFlip);                          
	    state.y = 0;                    
	    state.w = offset_x;                    
	    state.h = offset_y;  

	    destination.w = offset_x*zoom;      
	    destination.h = offset_y*zoom;       

	    if (nextDirection == DIR_UP)
	    {
	    	destination.x = (enemies[i].position).x;
	   	 	destination.y = (((enemies[i].position).y)-SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH; 
	    }

	    if (nextDirection == DIR_DOWN)
	    {
	    	destination.x = (enemies[i].position).x;
	   	 	destination.y = (((enemies[i].position).y)+SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH; 
	    }

	    if (nextDirection == DIR_LEFT)
	    {
	    	destination.x = (((enemies[i].position).x)-SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
	   	 	destination.y = (enemies[i].position).y;
	    }

	    if (nextDirection == DIR_RIGHT)
	    {
	    	destination.x = (((enemies[i].position).x)+SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
	   	 	destination.y = (enemies[i].position).y;
	    }

	    (enemies[i].position).x = destination.x;
	    (enemies[i].position).y = destination.y;

	    enemies[i].prevDirection = nextDirection;

	    SDL_RenderCopy(renderer, enemies[i].sprite, &state, &destination);  
    }
}