#include <SDL2/SDL.h>
#include <stdbool.h>
#include <wchar.h>

#include "sdl_handler.h"

void	clear_handler(sdl_handler_t* handler) {
	if (handler == NULL)
		return ;
	if (handler->renderer)
		SDL_DestroyRenderer(handler->renderer);
	if (handler->window)
		SDL_DestroyWindow(handler->window);
	if (handler->sdl_initiated)
		SDL_Quit();
	bzero(handler, sizeof(sdl_handler_t));
}

bool	init_handler(sdl_handler_t* handler) {
	bzero(handler, sizeof(sdl_handler_t));

    int error = SDL_Init(SDL_INIT_VIDEO);

	if (error != 0)
		goto error;
	SDL_Window* window = SDL_CreateWindow("chip-8", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, DISPLAY_SIZE_X, DISPLAY_SIZE_Y,
			SDL_WINDOW_MAXIMIZED);

	if (window == NULL)
		goto error;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
		goto error;
	return true;
error:
	fprintf(stderr, "%s", SDL_GetError());
	clear_handler(handler);
	return false;
}
