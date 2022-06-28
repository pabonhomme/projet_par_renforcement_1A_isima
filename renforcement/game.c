#include "game.h"

// verifie si le perso est sur un teleporteur, si oui il renvoie son indice dans le tableau, il renvoie -1 sinon
int hasToTeleport(Teleporter_t tabTeleporter[], Character_t character)
{
	int i = 0, hasToTeleport = -1;
	while(i < 2 && hasToTeleport == -1)
	{
		if(tabTeleporter[i].positionRow == character.row && tabTeleporter[i].positionColumn == character.column)
			hasToTeleport = i;
		i++;
	}

	return hasToTeleport;
}
