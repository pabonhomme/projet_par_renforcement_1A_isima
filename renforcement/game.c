#include "game.h"

void game_normal(){
  SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Window *window;
    SDL_Texture *texture[15], *sprite;
    SDL_Surface* image[15];

    Character_t character;
    Teleporter_t tabTeleporter[NB_TELEPORTER];

    initTeleporter(tabTeleporter);

    SDL_Rect source = {0};
	float zoom = 0.8;

    int running = 1, i = 0, j = 0, k = 0, offset_w, offset_h, cptCharac = 0, cptCharacMax = 6, action = -1, 
    movement = 1, teleport = -1, hasTeleported = 0, firstTeleport = 1,
    	grille [][25]={{1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},
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
    window = SDL_CreateWindow("Teleporting George", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    
    (character.position).x = 12*24-8;
    (character.position).y = 22*24+12;
    (character.position).w = offset_w*0.8;
    (character.position).h = offset_h*0.8;
    (character.state).x = 0;
    (character.state).y = 0;
    (character.state).w = offset_w;
    (character.state).h = offset_h;
    character.row = 23;
    character.column = 12;

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

        if (!movement && grille[character.row][character.column] == 4) 
        {
            if (zoom > 0) 
            {
              (character.state).x += offset_w; // La première vignette est en début de ligne
              (character.state).x %= source.w; // La vignette qui suit celle de fin de ligne est
              (character.position).w = offset_w * zoom; // Largeur du sprite à l'écran
              (character.position).h = offset_h * zoom; // Hauteur du sprite à l'écran 
              (character.position).x = (character.position).x + (offset_w * 0.05); // pour qu'il reste centré quand il diminue
              (character.position).y = (character.position).y + (offset_h * 0.05);
              zoom = zoom - 0.1;
            } 
            else 
            {
                (character.position).x = 12*24-8;
                (character.position).y = 22*24+12;
                (character.position).w = offset_w*0.8;
                (character.position).h = offset_h*0.8;
                (character.state).x = 0;
                (character.state).y = 0;
                (character.state).w = offset_w;
                (character.state).h = offset_h;
                character.row = 23;
                character.column = 12;
                k++;
                zoom = 0.8;
            }
        }
        else
        {
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
                        zoom += 0.1;
                        (character.state).x += offset_w;                // La première vignette est en début de ligne
                        (character.state).x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                        (character.position).w = offset_w * zoom;       // Largeur du sprite à l'écran
                        (character.position).h = offset_h * zoom;       // Hauteur du sprite à l'écran
                        (character.position).x = (character.position).x - (offset_w * 0.05); // pour qu'il reste centré quand il diminue
                        (character.position).y = (character.position).y - (offset_h * 0.05);
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
        }

        SDL_RenderCopy(renderer, character.sprite, &(character.state), &(character.position)); 
        SDL_Delay(50);

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

// verifie si le perso est sur un teleporteur, si oui il renvoie son indice dans le tableau, il renvoie -1 sinon
int hasToTeleport(Teleporter_t tabTeleporter[], Character_t character)
{
	int i = 0, hasToTeleport = -1;
	while(i < 20 && hasToTeleport == -1)
	{
		if(tabTeleporter[i].positionRow == character.row && tabTeleporter[i].positionColumn == character.column)
			hasToTeleport = i;
		i++;
	}

	return hasToTeleport;
}

void initTeleporter(Teleporter_t tabTeleporter[])
{
	Teleporter_t t3_1 = {3, 11, 13, 10},
    t3_2 = {13, 10, 3, 11},
    t6_1 = {20, 15, 17, 7},
    t6_2 = {17, 7, 20, 15},
    t7_1 = {2, 21, 17, 20},
    t7_2 = {17, 20, 2, 21},
    t8_1 = {15, 20, 21, 4},
    t8_2 = {21, 4, 15, 20},
    t9_1 = {10, 21, 6, 13},
    t9_2 = {6, 13, 10, 21},
    t10_1 = {18, 10, 20, 23},
    t10_2 = {20, 23, 18, 10},
    t11_1 = {9, 19, 12, 5},
    t11_2 = {12, 5, 9, 19},
    t12_1 = {1, 12, 12, 1},
    t12_2 = {12, 1, 1, 12},
    t13_1 = {3, 2, 21, 17},
    t13_2 = {21, 17, 3, 2},
    t14_1 = {2, 5, 9, 12},
    t14_2 = {9, 12, 2, 5};

    tabTeleporter[0] = t3_1;
    tabTeleporter[1] = t3_2;
    tabTeleporter[2] = t6_1;
    tabTeleporter[3] = t6_2;
    tabTeleporter[4] = t7_1;
    tabTeleporter[5] = t7_2;
    tabTeleporter[6] = t8_1;
    tabTeleporter[7] = t8_2;
    tabTeleporter[8] = t9_1;
    tabTeleporter[9] = t9_2;
    tabTeleporter[10] = t10_1;
    tabTeleporter[11] = t10_2;
    tabTeleporter[12] = t11_1;
    tabTeleporter[13] = t11_2;
    tabTeleporter[14] = t12_1;
    tabTeleporter[15] = t12_2;
    tabTeleporter[16] = t13_1;
    tabTeleporter[17] = t13_2;
    tabTeleporter[18] = t14_1;
    tabTeleporter[19] = t14_2;
}
// mettre un arriere plan 
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
//afficher un texte
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 255};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width+50;
    rect->h = text_height+30;
}
