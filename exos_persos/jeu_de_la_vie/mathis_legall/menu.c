#include "game.h"

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
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 0, 0, 0};

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

int menu(int * running_game)
{
	int running = 1, mode = 0;
    SDL_Texture *texture1, *texture2, *texture3, *texture4;
    SDL_Rect rect1,rect2, rect3, rect4;
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
  	bg_texture = IMG_LoadTexture(renderer,"./back.jpg");
  	if (bg_texture == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial_narrow_7.ttf", 34);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
        // get_text(renderer, 300-(rect1.w/2), 300, "Appuyez sur n pour monde normal",  font, &texture1, &rect1);
        // get_text(renderer,300-(rect1.w/2), 300 + rect1.h, "Appuyez sur t pour monde torique", font, &texture2, &rect2);
        // get_text(renderer,300-(rect1.w/2), 300 + rect2.h+rect1.h, "Appuyez sur s pour sauvegarder", font, &texture3, &rect3);
        // get_text(renderer,300-(rect1.w/2), 300 + rect3.h+rect2.h+rect1.h, "Appuyez sur c pour charger", font, &texture4, &rect4);

	while (running)
    {
			while (SDL_PollEvent(&event))
        	{	
            	switch (event.type)
            	{
            		case SDL_WINDOWEVENT:
                		switch (event.window.event)
                		{
                			case SDL_WINDOWEVENT_CLOSE:
                                *running_game=0;   
                    			break;
                			default:
                				break;
                		}
                	break;
                    case SDL_KEYDOWN:                                                                         
                        switch (event.key.keysym.sym){             
                        case SDLK_n:                                
                            printf("monde normal\n"); 
                            mode = 0;
                            running = 0;
                        break;
                        case SDLK_t:                                
                            printf("monde torique\n");  
                            mode = 1; 
                            running = 0;    
                        break;
                        case SDLK_ESCAPE:                           
                        case SDLK_q:                               
                        running =0;  
                        *running_game=0;                                                           
                        break;
                        default:                                    
                        break;
                    }
                    break;
            		case SDL_QUIT:
                		printf("on quitte\n");
                        *running_game=0;   
                		running = 0;
                		break;
            	}
            }
            SDL_RenderClear(renderer);
            display_background(bg_texture,window,renderer);
            get_text(renderer, 300-(rect1.w/2), 300-rect1.h/2, "Appuyez sur n pour monde normal",  font, &texture1, &rect1);
            get_text(renderer,300-(rect1.w/2), 300 + rect1.h/2, "Appuyez sur t pour monde torique", font, &texture2, &rect2);
            get_text(renderer,300-(rect1.w/2), 300 + rect1.h/2+rect2.h, "Appuyez sur s pour sauvegarder", font, &texture3, &rect3);
            get_text(renderer,300-(rect1.w/2), 300 + rect3.h+rect2.h+rect1.h/2, "Appuyez sur c pour charger", font, &texture4, &rect4);
            SDL_RenderCopy(renderer, texture1, NULL, &rect1);
            SDL_RenderCopy(renderer, texture2, NULL, &rect2);
            SDL_RenderCopy(renderer, texture3, NULL, &rect3);
            SDL_RenderCopy(renderer, texture4, NULL, &rect4);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            SDL_RenderClear(renderer);
      
    }
    
    //SDL_Delay(5000);
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return mode;
}