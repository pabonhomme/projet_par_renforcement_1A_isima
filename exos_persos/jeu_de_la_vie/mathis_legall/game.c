#include "game.h"

#include "game.h"

void charger(char* nomFichier,int **grid, int n)
{   
    FILE    * flot;
    int i,j;

    flot=fopen(nomFichier,"r"); // ouverture du fichier en lecture

    if (flot == NULL) // si l'ouverture s'est mal passee
    {
        printf("Problème d'ouverture du fichier\n");
    }
    if (feof(flot)) // si le fichier est vide
    {
        printf("fichier vide\n");
    }
    else
    {
    	for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				fscanf(flot,"%d", &grid[j][i]); // car matrice transposee
			}
		}
    }

    fclose(flot);
}

void sauvegarder(char* nomFichier, int **grid, int n)
{
    FILE * flot;
    int i,j;

    flot=fopen(nomFichier,"w"); // ouverture du fichier en ecriture

    if (flot == NULL) // si l'ouverture s'est mal passee
    {
        printf("Problème d'ouverture du fichier\n");
    }

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			fprintf(flot,"%d\t", grid[j][i]); // car matrice transposee quand on clique
		}
		fprintf(flot, "\n");
	}

    fclose(flot);
}

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
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

int menu(int * running_game, int *sauvegarde, int *chargement)
{
	int running = 1, mode = 0;
    SDL_Texture *texture1, *texture2, *texture3, *texture4;
    SDL_Rect rect1,rect2, rect3, rect4;
	SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;  
    int width = SIZEWINDOW;
    int height = SIZEWINDOW;                                                             
    SDL_Texture* bg_texture;   

                               

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
  	bg_texture = IMG_LoadTexture(renderer,"./back.jpg");
  	if (bg_texture == NULL) 
  		fprintf(stderr, "Erreur d'initialisation de la texture : %s\n", SDL_GetError());
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial_narrow_7.ttf", 34);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
        // get_text(renderer, 300-(rect1.w/2), 300, "Appuyez sur n pour monde normal",  font, &texture1, &rect1);
        // get_text(renderer,300-(rect1.w/2), 300 + rect1.h, "Appuyez sur t pour monde torique", font, &texture2, &rect2);
        // get_text(renderer,300-(rect1.w/2), 300 + rect2.h+rect1.h, "Appuyez sur s pour sauvegarder", font, &texture3, &rect3);
        // get_text(renderer,300-(rect1.w/2), 300 + rect3.h+rect2.h+rect1.h, "Appuyez sur c pour charger", font, &texture4, &rect4);

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
                                *running_game=0;   
                    			break;
                			default:
                				break;
                		}
                	break;
                    case SDL_KEYDOWN:                                                                         
                        switch (event.key.keysym.sym){             
                        case SDLK_n:                                
                            mode = 0;
                            running = 0;
                        break;
                        case SDLK_t:                                
                            mode = 1; 
                            running = 0;    
                        break;
                        case SDLK_s:                                
                            printf("Sauvegarde\n"); 
                            *sauvegarde = 1; 
                            running = 0;
                            break;
                        case SDLK_c:                                
                            printf("Charger config\n"); 
                            *chargement = 1; 
                            running = 0;
                            break;
                        case SDLK_ESCAPE:                           
                        case SDLK_q:                               
                        running =0;  
                        *running_game=0;                                                           
                        break;
                        default:                                    
                        break;
                    }
                    break;
            		case SDL_QUIT:
                        *running_game=0;   
                		running = 0;
                		break;
            	}
            }
            SDL_RenderClear(renderer);
            display_background(bg_texture,window,renderer);
            get_text(renderer, 300-(rect1.w/2), 300-rect1.h/2, "Appuyez sur n pour monde normal",  font, &texture1, &rect1);
            get_text(renderer,300-(rect1.w/2), 300 + rect1.h/2, "Appuyez sur t pour monde torique", font, &texture2, &rect2);
            get_text(renderer,300-(rect1.w/2), 300 + rect1.h/2+rect2.h, "Appuyez sur s pour sauvegarder", font, &texture3, &rect3);
            get_text(renderer,300-(rect1.w/2), 300 + rect3.h+rect2.h+rect1.h/2, "Appuyez sur c pour charger", font, &texture4, &rect4);
            SDL_RenderCopy(renderer, texture1, NULL, &rect1);
            SDL_RenderCopy(renderer, texture2, NULL, &rect2);
            SDL_RenderCopy(renderer, texture3, NULL, &rect3);
            SDL_RenderCopy(renderer, texture4, NULL, &rect4);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            SDL_RenderClear(renderer);
      
    }
    
    //SDL_Delay(5000);
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return mode;
}

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

int** mallocGrid(int n)
{
	int i;

	int** grid = (int**)malloc(n*sizeof(int*));
	
	for (i=0; i<n; i++)
	{
		grid[i] = (int*)malloc(n*sizeof(int));
	}

	return grid;
}

void initGrid(int n, int** grid)
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void printGrid(int n, int** grid)
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			printf("%d\t", grid[j][i]);
		}
		printf("\n");
	}
}

void newCell(int n, int i, int j, int** grid, int** copyGrid, int birth[], int survive[])
{
	int sumNeighbors;

	if(grid[i][j] == 1)
	{
		if (i == 0)
		{
			if (j == 0)
			{
				sumNeighbors = grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
				if(survive[sumNeighbors] == 1)
				{
					copyGrid[i][j] = 1;
				}
				else
				{
					copyGrid[i][j] = 0;
				}
			}
			else
			{
				if (j == n-1)
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j]+grid[i][j+1]+grid[i+1][j+1];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
			}
		}
		else
		{
			if (i == n-1)
			{
				if (j == 0)
				{
					sumNeighbors = grid[i][j+1]+grid[i-1][j+1]+grid[i-1][j];
					printf("%d\n",sumNeighbors);
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j]+grid[i][j+1]+grid[i-1][j+1];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
			else
			{
				if (j == 0)
				{
					sumNeighbors = grid[i-1][j]+grid[i-1][j+1]+grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
					if(survive[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i-1][j]+grid[i-1][j-1]+grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i-1][j-1]+grid[i-1][j]+grid[i-1][j+1]+
										grid[i][j-1]+grid[i][j+1]+grid[i+1][j-1]+
										grid[i+1][j]+grid[i+1][j+1];
						if(survive[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
		}
	}
	else
	{
		if (i == 0)
		{
			if (j == 0)
			{
				sumNeighbors = grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
				if(birth[sumNeighbors] == 1)
				{
					copyGrid[i][j] = 1;
				}
				else
				{
					copyGrid[i][j] = 0;
				}
			}
			else
			{
				if (j == n-1)
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
					if(birth[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					sumNeighbors = grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j]+grid[i][j+1]+grid[i+1][j+1];
					if(birth[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
			}
		}
		else
		{
			if (i == n-1)
			{
				if (j == 0)
				{
					sumNeighbors = grid[i][j+1]+grid[i-1][j+1]+grid[i-1][j];
					if(birth[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i][j-1]+grid[i-1][j-1]+grid[i-1][j]+grid[i][j+1]+grid[i-1][j+1];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
			else
			{
				if (j == 0)
				{
					sumNeighbors = grid[i-1][j]+grid[i-1][j+1]+grid[i][j+1]+grid[i+1][j+1]+grid[i+1][j];
					if(birth[sumNeighbors] == 1)
					{
						copyGrid[i][j] = 1;
					}
					else
					{
						copyGrid[i][j] = 0;
					}
				}
				else
				{
					if (j == n-1)
					{
						sumNeighbors = grid[i-1][j]+grid[i-1][j-1]+grid[i][j-1]+grid[i+1][j-1]+grid[i+1][j];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
					else
					{
						sumNeighbors = grid[i-1][j-1]+grid[i-1][j]+grid[i-1][j+1]+
										grid[i][j-1]+grid[i][j+1]+grid[i+1][j-1]+
										grid[i+1][j]+grid[i+1][j+1];
						if(birth[sumNeighbors] == 1)
						{
							copyGrid[i][j] = 1;
						}
						else
						{
							copyGrid[i][j] = 0;
						}
					}
				}
			}
		}
	}
}

void newGrid(int n, int** grid, int** copyGrid, int birth[], int survive[])
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			newCell(n,i,j,grid,copyGrid,birth,survive);
		}
	}
}

void freeGrid(int n, int** grid)
{
	int i;

	for (i=0; i<n; i++)
	{
		free(grid[i]);
	}

	free(grid);
}


void newCellToric(int n, int i, int j, int** grid, int** copyGrid, int birth[], int survive[])
{
	int sumNeighbors;
	sumNeighbors = grid[(i-1+n)%n][(j-1+n)%n]+grid[(i-1+n)%n][(j+n)%n]+grid[(i-1+n)%n][(j+1+n)%n]+
					   grid[(i+n)%n][(j-1+n)%n]+grid[(i+n)%n][(j+1+n)%n]+grid[(i+1+n)%n][(j-1+n)%n]+
					   grid[(i+1+n)%n][(j+n)%n]+grid[(i+1+n)%n][(j+1+n)%n];

	if (grid[i][j] == 1)
	{
		if (survive[sumNeighbors] == 1)
		{
			copyGrid[i][j] = 1;
		}
		else
		{
			copyGrid[i][j] = 0;
		}
	}
	else
	{
		if (birth[sumNeighbors] == 1)
		{
			copyGrid[i][j] = 1;
		}
		else
		{
			copyGrid[i][j] = 0;
		}
	}
}

void newGridToric(int n, int** grid, int** copyGrid, int birth[], int survive[])
{
	int i,j;

	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			newCellToric(n,i,j,grid,copyGrid,birth,survive);
		}
	}
}

int equalGrid(int n, int** grid1, int** grid2)
{
	int result = 0;
	int i = 0;
	int j = 0;

	while (i<n)
	{
		j=0;
		while (j<n)
		{
			if (grid1[i][j] == grid2[i][j])
			{
				result += 1;
			}

			j = j+1;
		}

		i = i+1;
	}
	if(result==(n*n)){
		result=1;
	}
	else{
		result=0;
	}

	return result;
}