#include <SDL2/SDL.h>
#include <stdio.h>




int main()
{
	SDL_Window *window = SDL_CreateWindow(
		"Window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1000, 1000,
		SDL_WINDOW_RESIZABLE);
	return 0;
}