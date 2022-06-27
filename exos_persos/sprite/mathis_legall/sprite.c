#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void background(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
}

void animatedSprite(SDL_Texture* bg, SDL_Texture* sprite, SDL_Window* window, SDL_Renderer* renderer)
{
	int nb_images = 6;
	int offset_x,offset_y;
	float zoom = 1.5;
	int x;
	int speed = 30;

	SDL_Rect 
            source = {0},                    
            window_dimensions = {0},         
            destination = {0},              
            state = {0};  

    SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);
    SDL_QueryTexture(sprite,NULL,NULL,&source.w, &source.h);

    offset_x = source.w/nb_images;
    offset_y = source.h/4;				   // Je n'ai qu'une seule ligne dans mon sprite

    state.x = 0;                          // La première vignette est en début de ligne
    state.y = 2*offset_y;                    // Une seule ligne
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;  

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

    destination.y = (window_dimensions.h - destination.h) /2 + 200; // on veut le voir courir au milieu de l'écran

    for (x=window_dimensions.w - destination.w; x>100; x -= speed) 
    {
    	 SDL_RenderClear(renderer); 
    	 background(bg,window,renderer);
         destination.x = x;                  
         state.x += offset_x;                
         state.x %= source.w;                 
                     
                  
         SDL_RenderCopy(renderer, sprite, &state, &destination);  
         SDL_RenderPresent(renderer);         
         SDL_Delay(100);                      
    }
    SDL_RenderClear(renderer);     
}
                         

int main()
{
	SDL_Texture* sprite;
	SDL_Texture* bg;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event event;
	SDL_bool program_on = SDL_TRUE; 

	window = SDL_CreateWindow("Window",	
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  1000, 1000,
							  SDL_WINDOW_RESIZABLE);
	if (window == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }

	sprite = IMG_LoadTexture(renderer,"monsprite.png");
	if (sprite == NULL)
	{
		 fprintf(stderr, "Erreur de chargement de l'image : %s\n", SDL_GetError());
	}

	bg = IMG_LoadTexture(renderer,"back.jpeg");
	if (sprite == NULL)
	{
		 fprintf(stderr, "Erreur de chargement de l'image : %s\n", SDL_GetError());
	}

	while (program_on == SDL_TRUE)
	{                           
		while (SDL_PollEvent(&event))
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
  		animatedSprite(bg,sprite,window,renderer);
  	}
  	SDL_DestroyTexture(bg);
    SDL_DestroyTexture(sprite);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

  	return 0;
}