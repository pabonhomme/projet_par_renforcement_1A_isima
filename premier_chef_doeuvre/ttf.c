#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT (WINDOW_WIDTH)

/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void get_text(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

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

int main(int argc, char **argv) {
    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Renderer *renderer;
    SDL_Texture *texture1;
    SDL_Window *window;
    char *font_path="./SIXTY.TTF";
    int quit;
    int i=5;
    char mot[10];
    sprintf(mot,"%d",i);

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
        get_text(renderer, 0, 0, mot,  font, &texture1, &rect1);
    

    quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        /* Use TTF textures. */
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);


        SDL_RenderPresent(renderer);
        i++;
        sprintf(mot,"%d",i);
        get_text(renderer, 0, 0, mot,  font, &texture1, &rect1);
        SDL_Delay(100);
    }

    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);

    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
} 
