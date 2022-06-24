#include <SDL2/SDL.h>
#include <stdio.h>

/********************************************/
/* Vérification de l'installation de la SDL */
/********************************************/
void CreateWindow(SDL_Window **tab){
  int i;
  int j=1;
  int x, y;
  for(i=0;i<=9;i++){
    tab[i]=NULL;
    tab[i]=SDL_CreateWindow("Fenêtre",50*i, 50*i, 200, 200,SDL_WINDOW_RESIZABLE);           
    if (tab[i]==NULL) {
      SDL_Log("Error : SDL window 1 creation - %s\n",SDL_GetError());                 
      SDL_Quit();                                    
      exit(EXIT_FAILURE);
    } 
  }
  SDL_GetWindowPosition(tab[9],&x,&y);
  for(i=10;i<=18;i++){
    tab[i]=NULL;
    tab[i]=SDL_CreateWindow("Fenêtre",450+50*j,450-50*j, 200, 200,SDL_WINDOW_RESIZABLE); 
    j++;        
    if (tab[i]==NULL) {
      SDL_Log("Error : SDL window 1 creation - %s\n",SDL_GetError());                 
      SDL_Quit();                                    
      exit(EXIT_FAILURE);
    } 
  }    
}
void Delete_Window(SDL_Window * tab []){
  int i;
  for(i=0;i<=18;i++){
    SDL_DestroyWindow(tab[i]);
}
}
void Move_WindowLeft(SDL_Window * tab [], int * continuer){
  int size;
  int x, y;
  int i;
  int window_x, window_y;
  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0, &mode);
  SDL_GetWindowPosition(tab[18],&x,&y);
  while (i<=18 && *continuer==0){
    if(x+250<=mode.w){
        SDL_GetWindowPosition(tab[i],&window_x, &window_y);
        SDL_SetWindowPosition(tab[i],window_x+50,window_y);
        i++;
    }
    else{
      *continuer = 1;
    }
  }      
}
void Move_WindowRight(SDL_Window * tab [], int * continuer){
  int size;
  int x, y;
  int i=0;
  int window_x, window_y;
  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0, &mode);
  SDL_GetWindowPosition(tab[0],&x,&y);
  while (i<=18 && *continuer==1){
    if(x-250>=0){
        SDL_GetWindowPosition(tab[i],&window_x, &window_y);
        SDL_SetWindowPosition(tab[i],window_x-50,window_y);
        i++;
    }
    else{
      *continuer = 0;
    }
  }      
}

int main(int argc, char **argv){
  (void)argc;
  (void)argv;
  SDL_Window * tab[18];
  SDL_bool
    program_on = SDL_TRUE,                          
    paused = SDL_FALSE;                             
  SDL_Event event;
  int sens= 1;
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  } 
  CreateWindow(tab);
  while (program_on) {                              
  while(SDL_PollEvent(&event)) { 
    if(program_on==SDL_TRUE){
      if(sens==0){
        Move_WindowLeft(tab, &sens);
      }
      else{
        Move_WindowRight(tab, &sens);
      }
      SDL_Delay(100);  
    }                                                     
    switch (event.type) {                    
      case SDL_QUIT:                                
        program_on = SDL_FALSE;                     
        break;
      case SDL_KEYDOWN:                                                                         
        switch (event.key.keysym.sym){             
        case SDLK_p:                                
        case SDLK_SPACE:                            
                                   
          break;
        case SDLK_ESCAPE:                           
        case SDLK_q:                               
          program_on = SDL_FALSE;                                                               
          break;
        default:                                    
          break;
        }
        break;
      default:                                    
        break;
    }
  }
  }
  Delete_Window(tab); 
  SDL_Quit();     
  return 0;
}
