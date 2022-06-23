#include "game.h"

// Affiche le background du menu
void display_background(SDL_Texture *bg_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
    source = {0},                         // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
    destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer
    SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(bg_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, bg_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher

}

// Insère le texte dans une surface
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

// gère les evenements du jeu
void handleEvent(SDL_Event event, int *running, int *currDirection, int* animFlip, SDL_Rect* position, int isDead)
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
						if (!isDead)
						{
							*currDirection = DIR_UP;
							*animFlip = 1 - *animFlip;
							position->y = ((position->y)-SPRITE_STEP+SCREEN_HEIGHT)%(SCREEN_HEIGHT);
						}
					break;

					case SDLK_DOWN:
						if (!isDead)
						{
							*currDirection = DIR_DOWN;
							*animFlip = 1 - *animFlip;
							position->y = ((position->y)+SPRITE_STEP+SCREEN_HEIGHT)%(SCREEN_HEIGHT);
						}	
						break;

					case SDLK_LEFT:
						if (!isDead)
						{
							*currDirection = DIR_LEFT;
							*animFlip = 1 - *animFlip;
							position->x = ((position->x)-SPRITE_STEP+SCREEN_WIDTH)%(SCREEN_WIDTH);
						}
						break;

					case SDLK_RIGHT:
						if (!isDead)
						{
							*currDirection = DIR_RIGHT;
							*animFlip = 1 - *animFlip;
							position->x = ((position->x)+SPRITE_STEP+SCREEN_WIDTH)%(SCREEN_WIDTH);
						}
						break;	

					default:
						break;
			}
			break;

		default:
			break;
	}
}

// initialise tous les
void initEnemies(Enemies_t enemies[], SDL_Texture* enemy)
{
	int i=0;
	SDL_Rect source = {0};

	SDL_QueryTexture(enemies[0].sprite, NULL, NULL, &source.w, &source.h);

	for (i=0; i<NB_ENEMIES_MAX; i++)
	{
		enemies[i].sprite = enemy;
		(enemies[i].position).x = rand()%(SCREEN_WIDTH-source.w/8); // abcisse aléatoire modulo la taille de la fenetre - la largeur du sprite de l'ennemi
    	(enemies[i].position).y = rand()%(SCREEN_HEIGHT-source.h);
    	(enemies[i].position).w = source.w/8;
    	(enemies[i].position).h = source.h;
    	enemies[i].prevDirection = rand()%4;
    	enemies[i].animFlip = 0;

	}
}
// mouvement du personnage
void moveCharacter(SDL_Texture* sprite, SDL_Renderer* renderer, SDL_Rect *position, int currDirection, int animFlip)
{
	int nb_images = 8;
	int offset_x,offset_y;
	float zoom = 2;

	SDL_Rect 
            source = {0},                            
             
            state = {0};  

    SDL_QueryTexture(sprite,NULL,NULL,&source.w, &source.h);

    offset_x = source.w/nb_images;
    offset_y = source.h;				  

    state.x = offset_x*(2*currDirection+animFlip);                          
    state.y = 0;                    
    state.w = offset_x;                    
    state.h = offset_y;  

    position->w = offset_x*zoom;      
    position->h = offset_y*zoom;       

    SDL_RenderCopy(renderer, sprite, &state, position);  
}


// direction choisie par la matrice des chaines de markov
int newDirection(int markov[][10], int prevDirection)
{
	int alpha = rand()%10;

	return (markov[prevDirection][alpha]);
}

// mouvement des ennemis en fonction des chaines de markov
void moveEnemies(Enemies_t enemies[], SDL_Renderer* renderer, int nb_enemies, int markov[][10])
{
	int nb_images = 8;
	int offset_x,offset_y;
	int i;
	int nextDirection;
	float zoom = 2;

	SDL_Rect 
            source = {0},                                         
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

	    (enemies[i].position).w = offset_x*zoom;      
	    (enemies[i].position).h = offset_y*zoom;       

	    if (nextDirection == DIR_UP)
	    {
	    	(enemies[i].position).x = (enemies[i].position).x;
	   	 	(enemies[i].position).y = (((enemies[i].position).y)-SPRITE_STEP+SCREEN_HEIGHT)%SCREEN_HEIGHT; 
	    }

	    if (nextDirection == DIR_DOWN)
	    {
	    	(enemies[i].position).x = (enemies[i].position).x;
	   	 	(enemies[i].position).y = (((enemies[i].position).y)+SPRITE_STEP+SCREEN_HEIGHT)%SCREEN_HEIGHT; 
	    }

	    if (nextDirection == DIR_LEFT)
	    {
	    	(enemies[i].position).x = (((enemies[i].position).x)-SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
	   	 	(enemies[i].position).y = (enemies[i].position).y;
	    }

	    if (nextDirection == DIR_RIGHT)
	    {
	    	(enemies[i].position).x = (((enemies[i].position).x)+SPRITE_STEP+SCREEN_WIDTH)%SCREEN_WIDTH;
	   	 	(enemies[i].position).y = (enemies[i].position).y;
	    }

	    enemies[i].prevDirection = nextDirection;

	    SDL_RenderCopy(renderer, enemies[i].sprite, &state, &(enemies[i].position));  
    }
}

// Creation d'un diamant sur la map
void create_diamond(SDL_Texture* diamond_texture, SDL_Renderer* renderer, int diamondLine, int diamondColumn, SDL_Rect *destination) 
{
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           state = {0};                     // Rectangle de la vignette en cours dans la planche 

     SDL_QueryTexture(diamond_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image
	int nb_images = 3;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 0.12;                        // zoom, car ces images sont un peu petites
       int largeurVignette = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
           hauteurVignette = source.h / 2;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = diamondColumn * largeurVignette ;                          // La première vignette est en début de ligne
       state.y = diamondLine * hauteurVignette;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = largeurVignette;                    // Largeur de la vignette
       state.h = hauteurVignette;                    // Hauteur de la vignette

       destination->w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       destination->h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran


     SDL_RenderCopy(renderer, diamond_texture,     // Préparation de l'affichage  
                    &state,
                    destination);            
}

// gestion des collisions entre le perso principal et la gestion des ennemis
int collisionEnemies(SDL_Rect positionCharac, Enemies_t enemies[], int nb_enemies)
{
	int i=0;
	int result = 0;
	int collision;

	while (!result && i<nb_enemies)
	{
		collision = SDL_HasIntersection(&positionCharac, &(enemies[i].position)) == SDL_TRUE ? 1 : 0;
		if (collision)
		{
			result = 1;
		}
		i++;
	}

	return result;
}
