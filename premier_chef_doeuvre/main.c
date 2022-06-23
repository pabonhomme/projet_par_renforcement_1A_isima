#include "game.h"

int main() {
    int running = 1;
    SDL_Rect rect_score;
	SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;                                                                
    SDL_Texture* bg_texture;
    SDL_Texture *score_texture;
    int i=5;
    char mot[100];
    char texte[100];
    strcpy(texte, "Score: ");
    sprintf(mot,"%d",i); 
    strcat(texte,mot);
    printf("%s\n",mot);
                                      

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
                            SCREEN_WIDTH , SCREEN_HEIGHT,
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
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./font/SIXTY.TTF", 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
        get_text(renderer, 0, 0, mot,  font, &score_texture, &rect_score);
    

  	bg_texture = IMG_LoadTexture(renderer,"./img/425.jpg");
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
        SDL_RenderClear(renderer);
        display_background(bg_texture,window,renderer);
        SDL_RenderCopy(renderer, score_texture, NULL, &rect_score);
        SDL_RenderPresent(renderer);
        i++;
        sprintf(mot,"%d",i);
        strcpy(texte, "");
        strcpy(texte, "Score: ");
        strcat(texte,mot);
        get_text(renderer, 0, 0, texte,  font, &score_texture, &rect_score);

        SDL_RenderPresent(renderer);         // Affichage                      
        SDL_RenderClear(renderer);
        SDL_Delay(100);
  
    }
    SDL_Delay(5000);
    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}