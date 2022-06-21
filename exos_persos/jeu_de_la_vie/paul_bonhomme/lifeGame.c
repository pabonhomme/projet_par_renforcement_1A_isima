#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define TAILLE 12

void initialize(int tab[][TAILLE])
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            tab[i][j] = 0;
        }
    }
}

void displayGrid(int tab[12][12])
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void displayRects(SDL_Rect rect, SDL_Renderer *renderer, int tab[][TAILLE])
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
        	if(tab[i][j] == 0)
        	{
        		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        	}
        	else
        	{
        		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        	}
            rect.x = 50 * i;
            rect.y = 50 * j;
            rect.w = rect.h = 50;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}

int main()
{
    int running = 1;
    int gameOn = 0;
    SDL_Event event;

    int tab[TAILLE][TAILLE];
    initialize(tab);
    displayGrid(tab);


    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window;
    int width = 600;
    int height = 600;

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    displayRects(rect, renderer, tab);

    // afficher à l'ecran
    SDL_RenderPresent(renderer);

    int test = 0, color = 0, occur = 0;
    int CaseX, CaseY;
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
                    	displayRects(rect, renderer, tab);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Case cliquée ");
                printf("Appui :%d %d\n", event.button.x, event.button.y);
                CaseX = event.button.x/50;
                CaseY = event.button.y/50;
                if(!gameOn)
                {
                	tab[CaseX][CaseY] = 1;
                }
                else
                {
                	// CODE MATHIS
                }
                displayRects(rect, renderer, tab);
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
        SDL_Delay(1); //  delai minimal
    }

    //SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}