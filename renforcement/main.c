#include "game.h"

int main()
{
    srand(time(NULL));
    // SDL_Renderer *renderer;
    // SDL_Event event;
    // SDL_Window *window;
    // SDL_Texture *texture[16], *sprite;
    // SDL_Surface* image[16];

    Character_t character;
    Teleporter_t tabTeleporter[NB_TELEPORTER];
    
    StateList_t stateList[NB_ITE+1];
    stateList[0].reward = 0;
    int hasWon = 0;

    initTeleporter(tabTeleporter);

    // SDL_Rect source = {0};
	float zoom = 0.8, max, eps = 1.0, epsRandom, qTable[NB_STATE][DIRECTION], xi = 0.8, gamma = 0.93, moy;

    initQtable(qTable);

    int nbV = 0,sumState = 0,running = 1, i = 0, j = 0, n =0, generation = 0, argmax, offset_w, offset_h, cptCharac = 0, cptCharacMax = 6, action = -1, 
    movement = 1, teleport = -1, hasTeleported = 0, firstTeleport = 1, nbState = 0,
    	grille [][25]={{1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},
                       {1,2,2,4,2,2,2,2,   1,2,2,2,12,2,2,2, 1,2,2,4,2,2,2,2,1},
                       {1,2,2,2,2,14,2,2,  1,2,2,2,2,4,2,2,  1,2,2,2,2,7,2,2,1},
                       {1,2,13,2,2,2,2,2,  1,2,2,3,2,2,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,4,2,   1,2,2,2,2,2,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,4,2,  1,2,4,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,2,   1,2,2,2,2,9,2,2,  1,2,2,2,2,2,4,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,2,2,  1,2,2,2,15,2,2,2,1},
                       {1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},

                       {1,2,2,2,4,2,2,2,   1,2,2,2,14,2,2,2, 1,2,2,11,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,4,2,2,2,2,2,  1,2,2,2,2,9,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,4,2,  1,2,2,4,2,2,2,2,1},
                       {1,12,2,2,2,11,2,2, 1,2,2,2,5,2,2,2,  1,2,2,2,2,2,2,4,1},
                       {1,2,2,2,2,2,2,2,   1,2,3,2,2,2,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,2,4,2,2,2,2,4,   1,2,2,2,2,2,2,15, 1,2,4,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,4,2,2,2,  1,2,2,2,8,2,2,2,1},
                       {1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},

                       {1,2,2,2,2,2,2,6,   1,2,2,2,4,2,2,2,  1,2,2,2,7,2,2,4,1},
                       {1,2,2,4,2,2,2,2,   1,2,10,2,2,2,4,2, 1,2,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,2,2,2,2,2,2,  1,2,4,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,4,   1,2,2,2,2,2,2,6,  1,2,2,2,2,2,2,10,1},
                       {1,2,2,2,8,2,2,2,   1,2,2,2,2,2,2,2,  1,13,2,2,2,2,2,2,1},
                       {1,2,2,2,2,2,2,2,   1,2,4,2,2,2,2,2,  1,2,2,2,2,2,2,2,1},
                       {1,2,2,4,2,2,2,2,   1,2,2,2,0,2,2,2,  1,2,2,2,2,4,2,2,1},
                       {1,1,1,1,1,1,1,1,   1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1},
                       };

    for (i=0; i<1000000; i++)
    {
    	initStateList(stateList);
        nbState = 0;
        hasWon = 0;
        character.row = 23;
        character.column = 12;

        while (!hasWon && nbState<NB_ITE)
        {
            argmax = 0;
            if (nbState == 0)
            {
                max = 0;
            }
            else
            {
                max = maxStateQtable(qTable, stateList[nbState-1].state, &argmax);            
            }
            epsRandom = (float)rand()/RAND_MAX;
           	//printf("eR:%f,e:%f\n",epsRandom,eps);
            if (epsRandom > eps) 
            {
                action = argmax;
            } 
            else 
            {
              action = rand() % 4;
            }

            // printf("Row:%d, Column:%d, Case:%d\n",character.row,character.column, grille[character.row][character.column]);
            // printf("Action:%d\n", action);
            stateList[nbState].state = 23 * (character.row - 1) + (character.column - 1);
            stateList[nbState].action = action;

            switch(action)
            {
                case UP:
                	if (grille[character.row-1][character.column] != 1)
                	{
                		character.row -= 1;
	                    switch (grille[character.row][character.column]) 
	                    {
	                    case 5:
	                      stateList[nbState + 1].reward = 1;
	                      break;
	                   
	                    default:
	                      stateList[nbState + 1].reward = 0;
	                      break;
	                    }
                	}
                    break;
                case DOWN:
                    if (grille[character.row+1][character.column] != 1)
                	{
                		character.row += 1;
	                    switch (grille[character.row][character.column]) 
	                    {
	                    case 5:
	                      stateList[nbState + 1].reward = 1;
	                      break;
	                    
	                    default:
	                      stateList[nbState + 1].reward = 0;
	                      break;
	                    }
                	}
                    break;
                case LEFT:
                    if (grille[character.row][character.column-1] != 1)
                	{
                		character.column -= 1;
	                    switch (grille[character.row][character.column]) 
	                    {
	                    case 5:
	                      stateList[nbState + 1].reward = 1;
	                      break;
	                    
	                    default:
	                      stateList[nbState + 1].reward = 0;
	                      break;
	                    }
                	}
                    break;
                case RIGHT:
                    if (grille[character.row][character.column+1] != 1)
                	{
                		character.column += 1;
	                    switch (grille[character.row][character.column]) 
	                    {
	                    case 5:
	                      stateList[nbState + 1].reward = 1;
	                      break;
	                   
	                      break;
	                    default:
	                      stateList[nbState + 1].reward = 0;
	                      break;
	                    }
                	}
                    break;
                default:
                    break;
            }
            nbState++;

            if(grille[character.row][character.column] == 4)
            {
            	stateList[nbState].state = 23 * (character.row - 1) + (character.column - 1);
            	stateList[nbState].action = action;
            	stateList[nbState+1].reward = 0;
            	nbState += 1;
                character.row = 23;
                character.column = 12;
                
            }
            else
            {
                teleport = hasToTeleport(tabTeleporter, character);

                if (teleport != -1) 
                {
                    stateList[nbState].state = 23 * (character.row - 1) + (character.column - 1);
            		stateList[nbState].action = action;
            		stateList[nbState+1].reward = 0;
            		nbState += 1;
                    character.row = tabTeleporter[teleport].destinationRow;
                    character.column = tabTeleporter[teleport].destinationColumn;
                }
                else
                {
                    if (grille[character.row][character.column] == 5)
                    {
                    	nbState++;
                        hasWon = 1;
                    }
                }
            }
        }
        if (i%150 == 0)
        {
        	eps *= 0.999;
        }
        
        printf("%d, %f, hasWon:%d\n", i,eps,hasWon);
        if (hasWon)
        {
        	sumState += nbState;
        	nbV++;
        	printf("%d,%d\n", sumState,nbV);
        	updateQtable(qTable, stateList, nbState, xi, gamma);
        	sauvegarder("sauvegarde.txt", qTable);
        }
        //printStateList(stateList,nbState);
        updateQtable(qTable, stateList, nbState, xi, gamma);
        //sauvegarder("sauvegarde.txt", qTable);
    }
    printf("%d\n", nbV);
    if (nbV > 0)
    {
    	moy = sumState/nbV;
    	printf("%f\n", moy);
    }

}
