#include "game.h"

void create_diamond(SDL_Texture* diamond_texture, int nbDiamond, SDL_Window* window, SDL_Renderer* renderer, int diamondLine, int diamondColumn, int destination_x, int destination_y ) 
{
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0},                // Rectangle définissant où la zone_source doit être déposée dans le renderer
           state = {0};                     // Rectangle de la vignette en cours dans la planche 

     SDL_QueryTexture(diamond_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image
	int nb_images = 3;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 0.12;                        // zoom, car ces images sont un peu petites
       int largeurVignette = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
           hauteurVignette = source.h / 2;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = diamondColumn * largeurVignette ;                          // La première vignette est en début de ligne
       state.y = diamondLine * hauteurVignette;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = largeurVignette;                    // Largeur de la vignette
       state.h = hauteurVignette;                    // Hauteur de la vignette

       destination.w = largeurVignette * zoom;       // Largeur du sprite à l'écran
       destination.h = hauteurVignette * zoom;       // Hauteur du sprite à l'écran



     destination.x = destination_x;

     destination.y = destination_y;


     SDL_RenderCopy(renderer, diamond_texture,     // Préparation de l'affichage  
                    &state,
                    &destination);            
   }