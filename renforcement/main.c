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
                            printf("%d\n", movement);
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

        printf("move:%d\n",movement);


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
    SDL_Delay(500);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

