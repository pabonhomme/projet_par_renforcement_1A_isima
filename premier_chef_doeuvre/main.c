#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SIZEWINDOW 600


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
    SDL_RenderPresent(renderer);         // Affichage
    SDL_Delay(50);                       // Pause en ms
    SDL_RenderClear(renderer);
}



int main(int argc, char** argv) {
    int running = 1;
	SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;  
    int width = SIZEWINDOW;
    int height = SIZEWINDOW;                                                               
    SDL_Texture* bg_texture; 

                                      

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur d'initialisation de TTF : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
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


  	bg_texture = IMG_LoadTexture(renderer,"./425.jpg");
  	if (bg_texture == NULL) 
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
            		case SDL_QUIT:
                		printf("on quitte\n");
                		running = 0;
                		break;
            	}
        	}
    display_background(bg_texture,window,renderer);
    }
    SDL_Delay(5000);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}