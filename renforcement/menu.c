#include <SDL2/SDL.h>
#include <stdio.h>
#include<string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

int main()
{
    SDL_Window* window; // fenetre de jeu
    SDL_Renderer* renderer; 
    SDL_Texture *texture;
    SDL_Rect rect, rect2;
    SDL_Rect surface;
    SDL_Texture *bg;
    int running=1;
    SDL_Event event;
    rect2.x = 260;
    rect2.y = 260;
    rect2.w = 50;
    rect2.h = 20;
    

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Game",  
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              600, 600,
                              SDL_WINDOW_RESIZABLE);
    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());

        // faire ce qu'il faut pour quitter proprement
    }
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./04B_19__.TTF", 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text(renderer, 0, 0, "Jouer",  font, &texture, &rect);
    

    bg= IMG_LoadTexture(renderer,"./img/bg.jpg");
    if (bg == NULL) 
        fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());  

    display_background(bg,window,renderer);
    SDL_RenderDrawRect(renderer, &rect2);
    
    while(running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:

                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        break;
                    
                    default:
                        break;      
                }
                break;
            case SDL_MOUSEBUTTONUP:
              if (   event.button.y > 260
                  && event.button.y <= 260+rect.h   
                  && event.button.x > 260
                  && event.button.x <= 260+rect.w){
                      printf("appui sur jouer\n");
                  }

            break;
            case SDL_QUIT:
                running = 0;
                break;
            }
        }
        SDL_RenderClear(renderer);
        // SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        display_background(bg,window,renderer);
        get_text(renderer, 260, 260, "Jouer",  font, &texture, &rect);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        
    }
    
    // SDL_RenderClear(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(bg);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}