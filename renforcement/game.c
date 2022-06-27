#include "game.h"


// Creation d'un diamant sur la map
void display_charac(SDL_Texture* character_texture, SDL_Renderer* renderer) 
{
	SDL_Rect source = {0},
			 destination = {0},                    // Rectangle définissant la zone de la texture à récupérer
           	 state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_QueryTexture(character_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image
	int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 1;                        // zoom, car ces images sont un peu petites
    int largeurVignette = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        hauteurVignette = source.h / nb_images;   // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 0 * largeurVignette ;                          // La première vignette est en début de ligne
       state.y = 0 * hauteurVignette;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = largeurVignette;                    // Largeur de la vignette
       state.h = hauteurVignette;                    // Hauteur de la vignette

       destination.w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       destination.h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran

       destination.x = 300;
       destination.y = 300;

     SDL_RenderCopy(renderer, character_texture,     // Préparation de l'affichage  
                    &state,
                    &destination);            	       
}

void teleport_to(SDL_Texture* character_texture, SDL_Renderer* renderer)
{
	SDL_Rect source = {0},
			 destination = {0},                    // Rectangle définissant la zone de la texture à récupérer
           	 state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_QueryTexture(character_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image
	int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 1;                        // zoom, car ces images sont un peu petites
    int largeurVignette = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        hauteurVignette = source.h / nb_images;   // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 0 * largeurVignette ;                          // La première vignette est en début de ligne
       state.y = 0 * hauteurVignette;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = largeurVignette;                    // Largeur de la vignette
       state.h = hauteurVignette;                    // Hauteur de la vignette

       destination.w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       destination.h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran

       destination.x = 300;
       destination.y = 300;

       for (int i = 0; i < 4; i++)
       {
       		state.x = i * largeurVignette;                // La première vignette est en début de ligne
       		SDL_RenderCopy(renderer, character_texture,     // Préparation de l'affichage  
                    &state,
                    &destination);
       }            	      
}