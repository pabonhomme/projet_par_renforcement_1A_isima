#include "pile.h"

void testFontion(void)
{
	Pile_t p;
	donnee_t haut, som;
	Boolean_t b;
	
	p = initPile();

	printf("Test affichage de la pile vide\n");
	afficherPile(p);

	printf("On empile 4 valeurs\n");
	p = empiler(p, 1);
	p = empiler(p, 2);
	p = empiler(p, 3);
	p = empiler(p, 4);
	afficherPile(p);

	printf("test sommet\n");
	som = sommet(p);
	printf("%d\n", som);

	printf("On dépile 2 valeurs\n");
	p = depiler(p);
	p = depiler(p);

	printf("test sommet\n");
	som = sommet(p);
	printf("sommet de la pile : %d\n", som);

	printf("test hauteur\n");
	haut = hauteur(p);
	printf("hauteur de la pile : %d\n", haut);

}

int main()
{
	testFontion();
	return 0;
}