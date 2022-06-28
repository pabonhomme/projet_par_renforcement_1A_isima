#include "game.h"

int main(){
    int running=1,i=0,j=0;
    int grille [][25]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,4,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,6,2,2,2,2,2,1,2,2,3,2,2,2,8,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,2,4,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,4,1,2,2,2,2,2,2,2,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,2,2,2,2,2,2,2,1,4,2,2,2,7,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,4,2,4,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,8,2,2,1,2,2,2,5,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,4,2,4,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,4,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,2,2,2,2,2,2,6,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,2,7,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,2,1,2,2,2,2,2,2,2,1,4,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,2,1,2,2,2,2,2,2,2,1,4,4,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,4,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,1,2,2,2,0,2,2,2,1,2,2,2,2,2,2,2,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       };

    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *texture1, 
                *texture2, 
                *texture3, 
                *texture4, 
                *texture5, 
                *texture6, 
                *texture7,
                *texture8,
                *texture9,
                *texture10;  // texture du message
    SDL_Window *window;

    SDL_Texture* sprite;
    Character_t character;
    SDL_Rect source = {0};
    int offset_w, offset_h, cptCharac = 0, cptCharacMax = 6, action, movement = 1;

    SDL_Surface* image1, 
                * image2, 
                * image3, 
                * image4, 
                * image5, 
                * image6, 
                * image7,
                * image8,
                * image9,
                *image10;

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
    image4 = IMG_Load("./img/green_button06.png");
    if(!image4)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture4=SDL_CreateTextureFromSurface(renderer,image4);
    SDL_FreeSurface(image4);
    image5 = IMG_Load("./img/green_button07.png");
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

    sprite = IMG_LoadTexture(renderer,"./img/george.png");
    if (sprite == NULL)
    {
         fprintf(stderr, "Erreur de chargement de l'image : %s\n", SDL_GetError());
    }

    character.sprite = sprite;
    
    SDL_QueryTexture(character.sprite,NULL,NULL,&source.w, &source.h);
    offset_w = source.w/4;
    offset_h = source.h/4;  
    
    (character.position).x = 17;
    (character.position).y = 10;
    (character.position).w = offset_w*0.8;
    (character.position).h = offset_h*0.8;
    (character.state).x = 0;
    (character.state).y = 0;
    (character.state).w = offset_w;
    (character.state).h = offset_h;
    character.row = 1;
    character.column = 1;
    
    image8 = IMG_Load("./img/red_button03.png");
    if(!image8)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture8=SDL_CreateTextureFromSurface(renderer,image8);
    SDL_FreeSurface(image8);
    image9 = IMG_Load("./img/redbutton.png");
    if(!image9)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture9=SDL_CreateTextureFromSurface(renderer,image9);
    SDL_FreeSurface(image9);
    image10 = IMG_Load("./img/yellow_button06.png");
    if(!image10)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    texture10=SDL_CreateTextureFromSurface(renderer,image10);
    SDL_FreeSurface(image10);
    image1 = IMG_Load("./img/black_button.png");
    if(!image1)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return -1;
    }
    SDL_RenderClear(renderer);
    texture1=SDL_CreateTextureFromSurface(renderer,image1);
    SDL_FreeSurface(image1);

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
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;

                        case SDLK_UP:
                            action = UP;
                            break;
                        case SDLK_RIGHT:
                            action = RIGHT;
                            break;
                        case SDLK_DOWN:
                            action = DOWN;
                            break;
                        case SDLK_LEFT:
                            action = LEFT;
                            break;


                        

            /*case SDL_QUIT:
                running = 0;
                break;*/
                }
            }
        }
        /* Affichage de la grille */
        for(i=0;i<25;i++){
            for(j=0;j<25;j++){
                SDL_Rect rect;
                rect.x=24*j;
                rect.y=24*i;
                rect.w=24;
                rect.h=24;
                
                switch(grille[i][j]){
                    case 0:
                        SDL_RenderCopy(renderer,texture4,NULL,&rect);
                    break;
                    case 1:
                        SDL_RenderCopy(renderer,texture6,NULL,&rect);
                    break;
                    case 2:
                        SDL_RenderCopy(renderer,texture3,NULL,&rect);
                    break;
                    case 3:
                        SDL_RenderCopy(renderer,texture2,NULL,&rect);
                    break;
                    case 4:
                        SDL_RenderCopy(renderer,texture1,NULL,&rect);
                    break;
                    case 5:
                        SDL_RenderCopy(renderer,texture5,NULL,&rect);
                    break;
                    case 6:
                        SDL_RenderCopy(renderer,texture10,NULL,&rect);
                    break;
                    case 7:
                        SDL_RenderCopy(renderer,texture9,NULL,&rect);
                    break;
                    case 8:
                        SDL_RenderCopy(renderer,texture8,NULL,&rect);
                    break;
                }
            }
        }

        // if (cptCharac == 0 && movement)
        // {
        //     action = 
        // }

        /* Animation personnage */
        if (movement)
        {
            switch(action)
            {
                case UP:
                    (character.state).x = 2*offset_w;
                    if (grille[character.row-1][character.column] != 1)
                    {
                        if (cptCharac != cptCharacMax)
                        {   
                            (character.position).y -= SPRITE_STEP;
                            (character.state).y += offset_h;
                            (character.state).y %= source.h;
                            cptCharac++;
                        }
                        else
                        {
                            character.row--;
                            cptCharac = 0;
                            action = -1;
                            //movement = 0;
                        }
                    }
                    break;

                case RIGHT:
                    (character.state).x = 3*offset_w;
                    if (grille[character.row][character.column+1] != 1)
                    {
                        if (cptCharac != cptCharacMax)
                        {   
                            (character.position).x += SPRITE_STEP;
                            (character.state).y += offset_h;
                            (character.state).y %= source.h;
                            cptCharac++;
                        }
                        else
                        {
                            character.column++;
                            cptCharac = 0;
                            action = -1;
                            //movement = 0;
                        }
                    }
                    break;

                case DOWN:
                    (character.state).x = 0;
                    if (grille[character.row+1][character.column] != 1)
                    {
                        if (cptCharac != cptCharacMax)
                        {   
                            (character.position).y += SPRITE_STEP;
                            (character.state).y += offset_h;
                            (character.state).y %= source.h;
                            cptCharac++;
                        }
                        else
                        {
                            character.row++;
                            cptCharac = 0;
                            action = -1;
                            //movement = 0;
                        }
                    }
                    break;

                case LEFT:
                    (character.state).x = offset_w;
                    if (grille[character.row][character.column-1] != 1)
                    {
                        if (cptCharac != cptCharacMax)
                        {   
                            (character.position).x -= SPRITE_STEP;
                            (character.state).y += offset_h;
                            (character.state).y %= source.h;
                            cptCharac++;
                        }
                        else
                        {
                            character.column--;
                            cptCharac = 0;
                            action = -1;
                            //movement = 0;
                        }
                    }
                    break;
            }
        }


        SDL_RenderCopy(renderer, character.sprite, &(character.state), &(character.position)); 
        SDL_Delay(60);

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
