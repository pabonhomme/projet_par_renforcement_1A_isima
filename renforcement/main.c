#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>


int main(){
    int running=1,i=0,j=0;
    int grille [][20]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       };
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *texture1, *texture2, *texture3, *texture4, *texture5, *texture6, *texture7;  // texture du message
    SDL_Window *window;
    SDL_Surface* image1, * image2, * image3, * image4, * image5, * image6, *image7;
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Initialisation des variables */
    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    }
    image1 = IMG_Load("./img/blue_boxCross.png");
    if(!image1)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture1=SDL_CreateTextureFromSurface(renderer,image1);
    SDL_FreeSurface(image1);
    image2 = IMG_Load("./img/blue_button06.png");
    if(!image2)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture2=SDL_CreateTextureFromSurface(renderer,image2);
    SDL_FreeSurface(image2);
    image3 = IMG_Load("./img/grey_button09.png");
    if(!image3)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture3=SDL_CreateTextureFromSurface(renderer,image3);
    SDL_FreeSurface(image3);
    image4 = IMG_Load("./img/red_button03.png");
    if(!image4)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture4=SDL_CreateTextureFromSurface(renderer,image4);
    SDL_FreeSurface(image4);
    image5 = IMG_Load("./img/red_button05.png");
    if(!image5)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture5=SDL_CreateTextureFromSurface(renderer,image5);
    SDL_FreeSurface(image5);
    image6 = IMG_Load("./img/tile_0000.png");
    if(!image6)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture6=SDL_CreateTextureFromSurface(renderer,image6);
    SDL_FreeSurface(image6);
    image7 = IMG_Load("./img/grey_sliderVertical.png");
    if(!image7)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture7=SDL_CreateTextureFromSurface(renderer,image7);
    SDL_FreeSurface(image7);
    
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
                    break;
                    	
                }
            }
        }
        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                SDL_Rect rect;
                rect.x=30*j;
                rect.y=30*i;
                rect.w=30;
                rect.h=30;
                if(grille[i][j]==0){
                    SDL_RenderCopy(renderer,texture4,NULL,&rect);
                    //SDL_RenderPresent(renderer);
                }
                else if(grille[i][j]==1){
                    SDL_RenderCopy(renderer,texture6,NULL,&rect);
                    
                    //SDL_RenderPresent(renderer);
                }
                else if(grille[i][j]==2){
                    SDL_RenderCopy(renderer,texture3,NULL,&rect);
                    //SDL_RenderPresent(renderer);
                }
                else if(grille[i][j]==5){
                    SDL_RenderCopy(renderer,texture5,NULL,&rect);
                    //SDL_RenderPresent(renderer);
                }
        }
    }
    SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);
    SDL_DestroyTexture(texture6);
    SDL_DestroyTexture(texture7);
    SDL_Delay(500);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
