#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
           

int main(int argc, char** argv) {

  srand(time(NULL));
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_DisplayMode screen;
         
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
            screen.h * 0.66,
            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0,"ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
  SDL_Rect rectangle[20]; 
                       // tableau de rectangle pour en avoir plusieurs                                        
  for (int i=0;i<20;i++) {      
    SDL_SetRenderDrawColor(renderer,    // creation de rectangles modelisant un serpent avec des couleurs aleatoires
                          rand()%255+20,           
                          rand()%255,       
                          rand()%255,          
                          255);                                    
    rectangle[i].x =  40*i; 
    rectangle[i].h = 10+i;                                                 
    rectangle[i].y =  20*i;                                                  
    rectangle[i].w = 50;                                               
     
    SDL_RenderDrawRect(renderer, &rectangle[i]);

  }


  SDL_RenderPresent(renderer);                         
  SDL_Delay(200); 
 
  while(1) {                                              // boucle infinie pour faire deplacer le serpent 
    SDL_SetRenderDrawColor(renderer,0, 0 , 0, 255);  

  SDL_RenderClear(renderer);
                                                              
  for (int i=0;i<20 ; i++) {   
      SDL_SetRenderDrawColor(renderer,
                              rand()%255 +20 ,           
                              rand()%255  ,       
                            rand()%255    ,          
                            255);                                    
      if(i<10){
        rectangle[i].x= rectangle[i].x+25;
      }        
      else{
        rectangle[i].y= rectangle[i].y+25;
      }                                          
                                                        
      SDL_RenderDrawRect(renderer, &rectangle[i]);
      SDL_RenderFillRect(renderer, &rectangle[i]);
                            
  }                                 
  SDL_RenderPresent(renderer);                         
  SDL_Delay(500);                                     
 }

  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_FAILURE;
}        
