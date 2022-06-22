#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
    SDL_Rect rect;
<<<<<<< HEAD
=======
    SDL_Renderer *renderer;
>>>>>>> e31fe01c39e3fd44c9c1e5ae159e7151c4b41de4
    int CaseX, CaseY;
    SDL_Window *window;
    int width = SIZEWINDOW;
    int height = SIZEWINDOW;
    int** grid = mallocGrid(SIZEGRID);
    int** copyGrid = mallocGrid(SIZEGRID);
    int** tmp;
    int speed = 300;
    int result = 0;
   
    TTF_Font* font = NULL;                                              
    font = TTF_OpenFont("LEMONMILK-Regular.otf", 65);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, "Jeu fixe!", color); // création du texte dans la surface 
    
    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

    SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);


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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        // faire ce qu'il faut pour quitter proprement
    }

<<<<<<< HEAD
    // couleur de fond
=======
>>>>>>> e31fe01c39e3fd44c9c1e5ae159e7151c4b41de4
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

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
                displayRects(rect, renderer, grid);
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym)
            	{
              		case SDLK_SPACE:
                		gameOn = 1;
                		break;
                	case SDLK_UP:
                        speed = speed*2;
                        break;

                    case SDLK_DOWN:
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
            }
        }
        if(gameOn)
        {
            newGridToric(SIZEGRID,grid,copyGrid,birth,survive);
        	result = equalGrid(SIZEGRID,grid,copyGrid);
            if (result)
            {
                printf("Jeu fixe");
                SDL_RenderCopy(renderer, text_texture, NULL, &pos);
            }
            tmp = grid;
        	grid = copyGrid;
        	copyGrid = tmp;
        	displayRects(rect, renderer, grid);
        }
        
        SDL_Delay(speed); //  delai minimal
    }
	freeGrid(SIZEGRID,grid);
	freeGrid(SIZEGRID,copyGrid);
    //SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}