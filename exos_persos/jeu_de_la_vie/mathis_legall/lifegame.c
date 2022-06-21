#include <SDL2/SDL.h>
#include "game.h"

#define SIZECELL 50 
#define SIZEWINDOW 600
#define SIZEGRID SIZEWINDOW/SIZECELL

void displayRects(SDL_Rect rect, SDL_Renderer *renderer, int** grid)
{
    int i,j;

    for (i = 0; i < SIZEGRID; i++)
    {
        for (j = 0; j < SIZEGRID; j++)
        {
        	if(grid[i][j] == 0)
        	{
        		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        	}
        	else
        	{
        		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        	}
            rect.x = SIZECELL * i;
            rect.y = SIZECELL * j;
            rect.w = rect.h = SIZECELL;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}

int main()
{
	int survive[9] = {0,0,1,1,0,0,0,0,0};
	int birth[9] = {0,0,0,1,0,0,0,0,0};
    int running = 1;
    int gameOn = 0;
    SDL_Event event;
    int test = 0, color = 0, occur = 0;
    int CaseX, CaseY;
    SDL_Window *window;
    int width = SIZEWINDOW;
    int height = SIZEWINDOW;
    int** grid = mallocGrid(SIZEGRID);
    int** copyGrid = mallocGrid(SIZEGRID);
    int** tmp;
    initGrid(SIZEGRID,grid);

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        // on peut aussi utiliser SLD_Log()
    }
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        // faire ce qu'il faut pour quitter proprement
    }

    SDL_Rect rect;

    // couleur de fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // dessiner CASES
    displayRects(rect, renderer, grid);

    // afficher à l'ecran
    SDL_RenderPresent(renderer);

    while (running)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                printf("window event\n");
                switch (event.window.event)
                {
                	case SDL_WINDOWEVENT_CLOSE:
                    	printf("appui sur la croix\n");
                    	break;
                	case SDL_WINDOWEVENT_SIZE_CHANGED:
                    	width = event.window.data1;
                    	height = event.window.data2;
                    	printf("Size : %d%d\n", width, height);
                	default:
                    	displayRects(rect, renderer, grid);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Case cliquée ");
                printf("Appui :%d %d\n", event.button.x, event.button.y);
                CaseX = event.button.x/SIZECELL;
                CaseY = event.button.y/SIZECELL;
                if(!gameOn)
                {
                	grid[CaseX][CaseY] = 1;
                }
                else
                {
                	newGrid(SIZEGRID,grid,copyGrid,birth,survive);
                	*tmp = *grid;
                	*grid = *copyGrid;
                	*copyGrid = *tmp;
                }
                displayRects(rect, renderer, grid);
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym)
            	{
              		case SDLK_SPACE:
                		gameOn = 1;
                		break;
                		
            	}
            	break;
            case SDL_QUIT:
                printf("on quitte\n");
                running = 0;
            }
        }
        SDL_Delay(100); //  delai minimal
    }
	freeGrid(SIZEGRID,grid);
	freeGrid(SIZEGRID,copyGrid);
    //SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}