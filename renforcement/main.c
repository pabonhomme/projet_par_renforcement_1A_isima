#include "game.h"

int main(){
    int running=1,i=0,j=0;

    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_Window *window;

    SDL_Texture* sprite;
    Character_t character;
    Teleporter_t tabTeleporter[NB_TELEPORTER], 
    t1 = {3, 2, 17, 7},
    t2 = {17, 7, 3, 2};
    tabTeleporter[0] = t1;
    tabTeleporter[1] = t2;
    SDL_Rect source = {0};

    int offset_w, offset_h, cptCharac = 0, cptCharacMax = 6, action, movement = 1, teleport = -1, hasTeleported = 0, firstTeleport = 1;
    float zoom = 0.8;

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

    SDL_Texture *texture[15];
    SDL_Surface* image[15];
    char * link[15]={"./img/green_button06.png",
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

    for(i=0;i<15;i++){
        image[i]=IMG_Load(link[i]);
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

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;

                        case SDLK_UP:
                            action = UP;
                            movement = 1;
                            break;
                        case SDLK_RIGHT:
                            action = RIGHT;
                            movement = 1;
                            break;
                        case SDLK_DOWN:
                            action = DOWN;
                            movement = 1;
                            break;
                        case SDLK_LEFT:
                            action = LEFT;
                            movement = 1;
                            break;
                        default:
                            break;
                }
                break;

            default:
                break;
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
                            movement = 0;
                            character.row--;
                            cptCharac = 0;
                            action = -1;
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
                            movement = 0;
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
                            movement = 0;
                            character.row++;
                            cptCharac = 0;
                            action = -1;
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
                            movement = 0;
                        }
                    }
                    break;
            }
        }
        
        teleport = hasToTeleport(tabTeleporter,character);

        if(teleport != -1 && movement==0)
        {
            if (firstTeleport)
            {
                if(zoom > 0)
                {
                    (character.state).x += offset_w;                // La première vignette est en début de ligne
                    (character.state).x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                    (character.position).w = offset_w * zoom;       // Largeur du sprite à l'écran
                    (character.position).h = offset_h * zoom;       // Hauteur du sprite à l'écran 
                    (character.position).x = (character.position).x + (offset_w * 0.05); // pour qu'il reste centré quand il diminue
                    (character.position).y = (character.position).y + (offset_h * 0.05);
                    zoom = zoom - 0.1;
                }
                else
                {
                    (character.position).x = 24*((tabTeleporter[teleport].destinationColumn))+17;
                    (character.position).y = 24*((tabTeleporter[teleport].destinationRow))+10;
                    character.row = tabTeleporter[teleport].destinationRow;
                    character.column = tabTeleporter[teleport].destinationColumn;
                    firstTeleport = 0;
                    hasTeleported = 1;
                }           
            }

            if(hasTeleported)
            {
                if(zoom < 0.8)
                {
                    (character.state).x += offset_w;                // La première vignette est en début de ligne
                    (character.state).x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                    (character.position).w = offset_w * zoom;       // Largeur du sprite à l'écran
                    (character.position).h = offset_h * zoom;       // Hauteur du sprite à l'écran
                    (character.position).x = (character.position).x - (offset_w * 0.05); // pour qu'il reste centré quand il diminue
                    (character.position).y = (character.position).y - (offset_h * 0.05);
                    zoom += 0.1;
                }
                else
                {
                    hasTeleported = 0;
                    firstTeleport = 1;
                    movement = 1;
                }
            }
        }
        else
        {
                movement = 1;
        }

        SDL_RenderCopy(renderer, character.sprite, &(character.state), &(character.position)); 
        SDL_Delay(60);

        SDL_RenderPresent(renderer);
    }

    for(i=0;i<15;i++){
        SDL_DestroyTexture(texture[i]);
    }

    SDL_Delay(500);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

