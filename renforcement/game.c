#include "game.h"

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