#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>


int main(){
    int running=1,i=0,j=0;
    int grille [][25]={{1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,12,2,2,2, 1,2,2,4,2,2,2,2,1},
                       {1,2,4,2,2,14,4,2,  1,2,2,4,4,2,2,2,  1,2,2,2,2,7,2,2,1},
                       {1,2,13,2,2,2,2,2,  1,2,2,3,2,2,2,2,  1,2,2,4,2,2,2,2,1},
                       {1,4,4,4,4,4,4,2,   1,2,2,2,2,2,2,2,  1,2,2,2,2,2,4,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,4,2,2,  1,2,4,2,4,2,2,2,1},
                       {1,2,4,2,2,2,2,2,   1,2,2,2,2,9,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,2,4,  1,2,4,2,2,2,2,2,1},
                       {1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},

                       {1,2,2,2,2,2,2,2,   1,4,2,2,14,2,2,2, 1,2,2,11,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,2,2,  1,2,2,2,2,9,2,2,1},
                       {1,2,2,4,2,2,2,2,   1,2,2,4,2,4,2,2,  1,2,2,4,2,2,2,2,1},
                       {1,12,2,2,4,11,2,2, 1,2,2,2,5,2,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,4,2,2,   1,2,3,4,2,4,2,2,  1,2,2,2,2,4,2,2,1},
                       {1,2,4,2,2,2,2,4,   1,2,2,2,2,2,2,2,  1,2,4,2,2,2,2,4,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,2,2,  1,2,2,2,8,2,2,2,1},
                       {1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},

                       {1,2,2,2,2,2,4,6,   1,4,4,4,2,2,2,2,  1,2,2,2,7,2,2,2,1},
                       {1,2,2,2,2,2,4,2,   1,4,10,2,2,2,2,2, 1,2,2,2,4,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,4,4,4,4,4,2,2,  1,4,2,2,2,2,2,4,1},
                       {1,2,4,4,4,4,4,4,   1,2,2,2,2,4,2,6,  1,4,4,2,2,2,2,10,1},
                       {1,2,2,2,8,2,2,2,   1,2,2,2,2,4,2,2,  1,13,2,2,2,2,2,4,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,2,2,  1,2,4,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,0,2,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},
                       };
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_Texture *texture[15];
    SDL_Window *window;
    SDL_Surface* image[15];
    char * source[15]={"./img/green_button06.png",
                       "./img/tile_0000.png",
                       "./img/grey_button09.png",
                       "./img/blue_button06.png",
                       "./img/tile_0043.png",
                       "./img/green_button07.png",
                       "./img/redbutton.png",
                       "./img/yellow_button06.png",
                       "./img/magenta_button.png",
                       "./img/sky_button.png",
                       "./img/olive_button.png",
                       "./img/pink_button.png",
                       "./img/purple_button.png",
                       "./img/brown_button.png",
                       "./img/red_button03.png"
                       };

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Initialisation des variables */
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    for(i=0;i<15;i++){
        image[i]=IMG_Load(source[i]);
        if(!image[i])
        {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
        }
        texture[i]=SDL_CreateTextureFromSurface(renderer,image[i]);
        SDL_FreeSurface(image[i]);
    }
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
                			default:
                				break;
                		}
                		break;
            		case SDL_QUIT:
                		
                		running = 0;
                		break;
            }
        }
        for(i=0;i<25;i++){
            for(j=0;j<25;j++){
                SDL_Rect rect;
                rect.x=24*j;
                rect.y=24*i;
                rect.w=24;
                rect.h=24;
                switch(grille[i][j]){
                    case 0:
                        SDL_RenderCopy(renderer,texture[0],NULL,&rect);
                    break;
                    case 1:
                        SDL_RenderCopy(renderer,texture[1],NULL,&rect);
                    break;
                    case 2:
                        SDL_RenderCopy(renderer,texture[2],NULL,&rect);
                    break;
                    case 3:
                        SDL_RenderCopy(renderer,texture[3],NULL,&rect);
                    break;
                    case 4:
                        SDL_RenderCopy(renderer,texture[4],NULL,&rect);
                    break;
                    case 5:
                        SDL_RenderCopy(renderer,texture[5],NULL,&rect);
                    break;
                    case 6:
                        SDL_RenderCopy(renderer,texture[6],NULL,&rect);
                    break;
                    case 7:
                        SDL_RenderCopy(renderer,texture[7],NULL,&rect);
                    break;
                    case 8:
                        SDL_RenderCopy(renderer,texture[8],NULL,&rect);
                    break;
                    case 9:
                        SDL_RenderCopy(renderer,texture[9],NULL,&rect);
                    break;
                    case 10:
                        SDL_RenderCopy(renderer,texture[10],NULL,&rect);
                    break;
                    case 11:
                        SDL_RenderCopy(renderer,texture[11],NULL,&rect);
                    break;
                    case 12:
                        SDL_RenderCopy(renderer,texture[12],NULL,&rect);
                    break;
                    case 13:
                        SDL_RenderCopy(renderer,texture[13],NULL,&rect);
                    break;
                    case 14:
                        SDL_RenderCopy(renderer,texture[14],NULL,&rect);
                    break;

                }
            }
    SDL_RenderPresent(renderer);
        }
    }
    for(i=0;i<15;i++){
        SDL_DestroyTexture(texture[i]);
    }

    SDL_Delay(500);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
