#include "game.h"

int main()
{
	int survive[9] = {0,0,1,1,0,0,0,0,0};
	int birth[9] = {0,0,0,1,0,0,0,0,0};
    int running = 1, gameOn = 0, mode = 0, sauvegarde = 0, chargement = 0, endGame = 0;
    SDL_Event event;
    SDL_Rect rect;
    SDL_Rect rect_mess;
    int CaseX, CaseY;
    SDL_Renderer *renderer;
    SDL_Texture *texture_mess;
    SDL_Window *window;
    int width = SIZEWINDOW;
    int height = SIZEWINDOW;
    int** grid = mallocGrid(SIZEGRID);
    int** copyGrid = mallocGrid(SIZEGRID);
    int** tmp;
    int speed = 300;
    int result = 0;
    void (* tabMode[2])(int, int**, int**, int*, int *) = {newGrid, newGridToric}; // pointeur de fonction en fonction du mode thorique ou non
   
    TTF_Font* font;                                              


    initGrid(SIZEGRID,grid);

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    mode = menu(&running, &sauvegarde, &chargement);

    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        // on peut aussi utiliser SLD_Log()
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    TTF_Init();
    font = TTF_OpenFont("arial_narrow_7.ttf", 32);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    

    // couleur de fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    displayRects(rect, renderer, grid);

    // afficher à l'ecran

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
                    	displayRects(rect, renderer, grid);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(!chargement)
                {
                    CaseX = event.button.x/SIZECELL;
                    CaseY = event.button.y/SIZECELL;
                    if(!gameOn)
                    {
                        grid[CaseX][CaseY] = 1;
                    }
                }
                displayRects(rect, renderer, grid);
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym)
            	{
              		case SDLK_SPACE:
                        if(sauvegarde)
                        {
                            printGrid(SIZEGRID, grid);
                            sauvegarder("sauvegarde.txt", grid, SIZEGRID);
                            running = 0;
                        }
                        else
                        {
                		  gameOn = 1;
                        }
                		break;
                	case SDLK_LEFT:
                        speed = speed*2;
                        break;

                    case SDLK_RIGHT:
                        speed = speed/2;
                        break;    

                    default:
                		break;	       		
            	}
            	break;
            case SDL_QUIT:
                printf("on quitte\n");
                running = 0;
                break;
            default: 
                if(chargement)
                {
                    charger("sauvegarde.txt", grid, SIZEGRID);
                    displayRects(rect, renderer, grid);
                    chargement = 0;
                }
                break;
            }
        }
        
            if(gameOn)
            {
                tabMode[mode](SIZEGRID,grid,copyGrid,birth,survive);
                
                tmp = grid;
                grid = copyGrid;
                copyGrid = tmp;
                displayRects(rect, renderer, grid);
                //SDL_RenderPresent(renderer);
                //SDL_Delay(100);
                SDL_RenderClear(renderer);
                result = equalGrid(SIZEGRID,grid,copyGrid);
                if (result)
                {
                    endGame = 1; 
                    gameOn = 0;

                }
            }
            if(endGame)
            {
                SDL_RenderClear(renderer);
                displayRects(rect, renderer, grid);
                get_text(renderer, 300-(rect_mess.w/2), 300-(rect_mess.h/2), "JEU FIXE",  font, &texture_mess, &rect_mess);
                SDL_RenderCopy(renderer, texture_mess, NULL, &rect_mess);
                SDL_RenderPresent(renderer);
            }

        
        
        SDL_Delay(speed); //  delai minimal
    }
	freeGrid(SIZEGRID,grid);
	freeGrid(SIZEGRID,copyGrid);
    //SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}