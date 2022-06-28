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

void initCharacter(Character_t character, SDL_Texture* sprite)
{
	SDL_Rect source = {0};
	int offset_w, offset_h;

	character.sprite = sprite;

	SDL_QueryTexture(character.sprite,NULL,NULL,&source.w, &source.h);
    offset_w = source.w/4;
    offset_h = source.h/4;  

	(character.position).x = 17;
	(character.position).y = 10;
	(character.position).w = offset_w * 0.8;
	(character.position).h = offset_h * 0.8;
	(character.state).x = 0;
	(character.state).y = 0;
	(character.state).w = offset_w;
	(character.state).h = offset_h;
	character.row = 1;
	character.column = 1;
}