#include "game.h"

// verifie si le perso est sur un teleporteur, si oui il renvoie son indice dans le tableau, il renvoie -1 sinon
int hasToTeleport(Teleporter_t tabTeleporter[], Character_t character)
{
	int i = 0, hasToTeleport = -1;
	while(i < 22 && hasToTeleport == -1)
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
    t14_2 = {9, 12, 2, 5},
    t15_1 = {7, 20, 14, 15},
    t15_2 = {14, 15, 7, 20};

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
    tabTeleporter[20] = t15_1;
    tabTeleporter[21] = t15_2;
}

void initQtable(float qTable[][DIRECTION])
{
	int i,j;

	for (i=0; i<NB_STATE; i++)
	{
		for (j=0; j<DIRECTION; j++)
		{
			qTable[i][j] = 0;
		}
	}
}

float maxStateQtable(float qtable[][DIRECTION], int state, int *argmax)
{
	int i;
	float max = qtable[state][0];

	for (i=1; i<DIRECTION; i++)
	{
		if (qtable[state][i] > max)
		{
			max = qtable[state][i];
			*argmax = i;
		}
	}

	return max;
}

void updateQtable(float qTable[][DIRECTION], StateList_t stateList[], int nbState, float xi, float gamma)
{
	int i = nbState-1;
	float m;
	int argmax = 0;

	qTable[stateList[i-1].state][stateList[i-1].action] += xi*(stateList[i].reward - qTable[stateList[i-1].state][stateList[i-1].action]);

	for (i=nbState-3; i>0; i--)
	{
		m = maxStateQtable(qTable, stateList[i+1].state,&argmax);
		qTable[stateList[i].state][stateList[i].action] += xi*(stateList[i+1].reward + gamma*m - qTable[stateList[i].state][stateList[i].action]);
	}
}

void printQtable(float qTable[][DIRECTION])
{
	int i,j;

	for (i=0; i<NB_STATE; i++)
	{
		for (j=0; j<DIRECTION; j++)
		{
			printf("%d : %f ",i,qTable[i][j]);
		}
		printf("\n");
	}
}

void printStateList(StateList_t stateList[], int nbState)
{
	int i;

	for (i=0; i<nbState; i++)
	{
		printf("State: %d, Action: %d, Reward: %d\n",stateList[i].state, stateList[i].action, stateList[i].reward);
	}
}

/* Fonction qui remplit une matrice à partir d'un fichier*/
void charger(char* nomFichier,float grid[][DIRECTION])
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
        for (i=0; i<NB_STATE; i++)
        {
            for (j=0; j<DIRECTION; j++)
            {
                fscanf(flot,"%f", &grid[i][j]); 
            }
        }
    }

    fclose(flot);
}

/* Fonction qui sauvegarde une matrice dans un fichier*/
void sauvegarder(char* nomFichier, float grid[][DIRECTION])
{
    FILE * flot;
    int i,j;

    flot=fopen(nomFichier,"w"); // ouverture du fichier en ecriture

    if (flot == NULL) // si l'ouverture s'est mal passee
    {
        printf("Problème d'ouverture du fichier\n");
    }

    for (i=0; i<NB_STATE; i++)
    {
        for (j=0; j<DIRECTION; j++)
        {
            fprintf(flot,"%f\t", grid[i][j]); 
        }
        fprintf(flot, "\n");
    }

    fclose(flot);
}