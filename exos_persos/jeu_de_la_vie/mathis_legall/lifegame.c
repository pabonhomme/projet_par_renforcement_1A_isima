#include "game.h"

int main()
{
	int survive[9] = {0,0,1,1,0,0,0,0,0};
	int birth[9] = {0,0,0,1,0,0,0,0,0};
    int running = 1, gameOn = 0, mode = 0, sauvegarde = 0, chargement = 0, endGame = 0;
    SDL_Event event;
    SDL_Rect rect;
    SDL_Rect rect_mess;         // rectangle du message
    int CaseX, CaseY;
    SDL_Renderer *renderer;
    SDL_Texture *texture_mess;  // texture du message
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

    /* Appel du menu */
    mode = menu(&running, &sauvegarde, &chargement);

    /* Initialisation des variables */
    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
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

    /* Initialisation de la police */
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
                    CaseX = event.button.x/SIZECELL;        // Case cliquée en X
                    CaseY = event.button.y/SIZECELL;        // Case cliquée en Y
                    if(!gameOn)
                    {
                        if (grid[CaseX][CaseY] == 1)        // si la case est déjà noire, on la met en blanc
                        {
                            grid[CaseX][CaseY] = 0;
                        }
                        else
                        {
                            grid[CaseX][CaseY] = 1;
                        }
                    }
                }
                displayRects(rect, renderer, grid);
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym)
            	{
              		case SDLK_SPACE:
                        if(sauvegarde)  // si on est dans le mode sauvegarde 
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
                	case SDLK_LEFT:        // gestion de la vitesse
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
                if(chargement)          // si on est dans le mode chargement 
                {
                    charger("sauvegarde.txt", grid, SIZEGRID);
                    displayRects(rect, renderer, grid);
                    chargement = 0;     // on ne charge qu'une seule fois 
                }
                break;
            }
        }
        
            if(gameOn)
            {
                tabMode[mode](SIZEGRID,grid,copyGrid,birth,survive); // utilisation du pointeur de fonction suivant le mode 
                
                tmp = grid;             // on passe la nouvelle matrice en matrice courante
                grid = copyGrid;        // on passe l'ancienne en matrice copie
                copyGrid = tmp;
                displayRects(rect, renderer, grid);
                SDL_RenderClear(renderer);
                result = equalGrid(SIZEGRID,grid,copyGrid);
                if (result)
                {
                    endGame = 1;    // on change la fin du jeu
                    gameOn = 0;     // on arrête la partie

                }
            }
            if(endGame)
            {
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 255,255,255,255);
                displayRects(rect, renderer, grid);
                get_text(renderer, 300-(rect_mess.w/2), 300-(rect_mess.h/2), "JEU FIXE",  font, &texture_mess, &rect_mess);
                SDL_RenderCopy(renderer, texture_mess, NULL, &rect_mess);
                SDL_RenderPresent(renderer);
            }
     
        SDL_Delay(speed); //  delai géré avec le paramètre vitesse
    }

	freeGrid(SIZEGRID,grid);
	freeGrid(SIZEGRID,copyGrid);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}