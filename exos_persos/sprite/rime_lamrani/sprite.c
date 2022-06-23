#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

#define SIZEWINDOW 600




void moveTexture(SDL_Texture* my_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
       SDL_Rect 
             source = {0},                    // Rectangle définissant la zone totale de la planche
             window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
             destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
             state = {0};                     // Rectangle de la vignette en cours dans la planche 

       SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                         &window_dimensions.w,
                         &window_dimensions.h);
       SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

       /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

       int nb_images = 4;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 0.5;                        // zoom, car ces images sont un peu petites
       int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
           offset_y = source.h / 13;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 0 ;                          // La première vignette est en début de ligne
       state.y = 0 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = offset_x;                    // Largeur de la vignette
       state.h = offset_y;                    // Hauteur de la vignette

       destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
       destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

       destination.y =                        // La course se fait en milieu d'écran (en vertical)
         (window_dimensions.h - destination.h) /2;

       int speed = 6;
       for (int x = window_dimensions.w - destination.w; x >0 ; x -= speed) {
       	SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
         destination.x = x;                   // Position en x pour l'affichage du sprite
         state.x += offset_x;                 // On passe à la vignette suivante dans l'image
         state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de début de ligne

         SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                        &state,
                        &destination);  
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(100);                       // Pause en ms
       }
       SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
   }

   int main()
{
	int running = 1;
	SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;  
    int width = SIZEWINDOW;
    int height = SIZEWINDOW;                           
    SDL_Texture* cat_texture;                                   

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
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
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);

    cat_texture = IMG_LoadTexture(renderer,"chat.png");
  
  	if (cat_texture == NULL) 
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
        if(running)
        {
        	moveTexture(cat_texture, window, renderer);
        }
      
    }
    
    //SDL_Delay(5000);
    SDL_DestroyTexture(cat_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
} 
