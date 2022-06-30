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
    
    StateList_t stateList[500];
    stateList[0].reward = 0;
    int hasWon = 0;

    initTeleporter(tabTeleporter);

    // SDL_Rect source = {0};
	float zoom = 0.8, max, eps = 1.0, epsRandom, qTable[NB_STATE][DIRECTION], xi = 0.99, gamma = 0.9;

    initQtable(qTable);

    int running = 1, i = 0, j = 0, n =0, generation = 0, argmax, offset_w, offset_h, cptCharac = 0, cptCharacMax = 6, action = -1, 
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

    for (i=0; i<1000; i++)
    {
        nbState = 0;
        hasWon = 0;
        while (!hasWon && nbState<400)
        {
            argmax = 0;
            if (nbState == 0)
            {
                max = 0;
            }
            else
            {
                max = maxStateQtable(qTable, stateList[nbState-1].state, &argmax);            epsRandom = (float) rand() / RAND_MAX;
            }

            if (epsRandom > eps) 
            {
              if (max > 0) 
              {
                action = argmax;
              } 
              else 
              {
                action = rand() % 4;
              }
            } 
            else 
            {
              action = rand() % 4;
            }

            stateList[nbState].state = 23 * (character.row - 1) + (character.column - 1);

            switch(action)
            {
                case UP:
                    character.row -= 1;
                    stateList[nbState].action = action;
                    switch (grille[character.row][character.column]) 
                    {
                    case 5:
                      stateList[nbState + 1].reward = 10;
                      break;

                    default:
                      stateList[nbState + 1].reward = 0;
                      break;
                    }
                    break;
                case DOWN:
                    character.row += 1;
                    stateList[nbState].action = action;
                    switch (grille[character.row][character.column]) 
                    {
                    case 5:
                      stateList[nbState + 1].reward = 10;
                      break;

                    default:
                      stateList[nbState + 1].reward = 0;
                      break;
                    }
                    break;
                case LEFT:
                    character.column -= 1;
                    stateList[nbState].action = action;
                    switch (grille[character.row][character.column]) 
                    {
                    case 5:
                      stateList[nbState + 1].reward = 10;
                      break;

                    default:
                      stateList[nbState + 1].reward = 0;
                      break;
                    }
                    break;
                case RIGHT:
                    character.column += 1;
                    stateList[nbState].action = action;
                    switch (grille[character.row][character.column]) 
                    {
                    case 5:
                      stateList[nbState + 1].reward = 10;
                      break;

                    default:
                      stateList[nbState + 1].reward = 0;
                      break;
                    }
                    break;
                default:
                    break;
            }
            nbState++;

            if(grille[character.row][character.column] == 4)
            {
                character.row = 23;
                character.column = 12;
            }
            else
            {
                teleport = hasToTeleport(tabTeleporter, character);

                if (teleport != -1) 
                {
                    character.row = tabTeleporter[teleport].destinationRow;
                    character.column = tabTeleporter[teleport].destinationColumn;
                }
                else
                {
                    if (grille[character.row][character.column] == 5)
                    {
                        sauvegarder("sauvegarde.txt", qTable);
                        hasWon = 1;
                    }
                }
            }
            if (nbState % 500 == 0) 
            {
                eps *= 0.99;
            }
        }
        updateQtable(qTable, stateList, nbState, xi, gamma);   
    }
}
