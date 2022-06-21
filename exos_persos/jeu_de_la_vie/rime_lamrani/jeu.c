#include <SDL2/SDL.h>
#include <stdio.h>

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer) {                              // renderer à fermer
  char msg_formated[255];                                                         
  int l;                                                                          

  if (!ok) {                                                        // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);                                              
    l = strlen(msg_formated);                                                     
    strcpy(msg_formated + l, " : %s\n");                                          

    SDL_Log(msg_formated, SDL_GetError());                                        
  }                                                                               

  if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
    window= NULL;
  }

  SDL_Quit();                                                                     

  if (!ok) {                                                        // On quitte si cela ne va pas                
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}                 

int main(int argc, char **argv){
    (void)argc;
    (void)argv;
    int width = 600;
    int height = 600;
    int CaseX, CaseY;
    SDL_Window * window;
    SDL_Renderer* renderer = NULL;
    int program_on =1;                            
    SDL_Event event;
    SDL_Rect rect;
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } 
    window=NULL;
    window=SDL_CreateWindow("Fenêtre", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_RESIZABLE);           
    if (window==NULL) {
      SDL_Log("Error : SDL window 1 creation - %s\n",SDL_GetError());                 
      SDL_Quit();                                    
      exit(EXIT_FAILURE);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    
    SDL_RenderDrawRect(renderer,&rect);
    rect.x = 50;
    rect.y = 50;
    rect.w = rect.h = 50;
    SDL_SetRenderDrawColor(renderer,0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer); 
    while (program_on) {                              // La boucle des évènements
      while(SDL_PollEvent(&event)) {             // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
        switch (event.type) {                         // En fonction de la valeur du type de cet évènement
          case SDL_WINDOWEVENT:
            printf("window event\n");
              switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                printf("appui sur la croix\n");
                program_on=0;
                break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                width = event.window.data1;
                height = event.window.data2;
                SDL_RenderSetLogicalSize(renderer, 600, 600);
                }
            break;
        case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée 
            switch (event.key.keysym.sym) {             // la touche appuyée est ..
            case SDLK_ESCAPE:                           // 'ESCAPE'  
            case SDLK_q:                                // ou 'q'
                program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
            break;
            default:                                    // Une touche appuyée qu'on ne traite pas
            break;
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
            CaseX = event.button.x/50;
            CaseY = event.button.y/50;
            printf("%d %d\n", CaseX, CaseY);
            printf("%d %d\n", rect.x, rect.y);
            if((rect.x/50==CaseX) && (rect.y/50==CaseY)){
              SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
              SDL_RenderFillRect(renderer, &rect);
              SDL_RenderPresent(renderer); 
            }   
        break;
        default:                                      // Les évènements qu'on n'a pas envisagé
        break;
        }
  }                                          // Petite pause
}          
    SDL_Delay(500);  
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();     
    return 0;
}