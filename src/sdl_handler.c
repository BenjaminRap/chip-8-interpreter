#include <SDL2/SDL.h>
#include <stdbool.h>

#include "sdl_handler.h"

void	clear_handler(sdl_handler_t* handler) {
	if (!handler)
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

    int error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	if (error)
		goto error;
	handler->sdl_initiated = true;
	handler->window = SDL_CreateWindow("chip-8", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, DISPLAY_SIZE_X, DISPLAY_SIZE_Y,
			SDL_WINDOW_MAXIMIZED);

	if (!handler->window)
		goto error;

	handler->renderer = SDL_CreateRenderer(handler->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!handler->renderer)
		goto error;
	return true;
error:
	fprintf(stderr, "%s\n", SDL_GetError());
	clear_handler(handler);
	return false;
}

bool	sdl_clear_handler(sdl_handler_t* handler) {
	if (SDL_SetRenderDrawColor(handler->renderer, 0, 0, 0, 255) < 0
		|| SDL_RenderClear(handler->renderer) < 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return false;
	}
    SDL_RenderPresent(handler->renderer);
	return true;
}

bool	sdl_display(sdl_handler_t* handler, void* sprite, uint8_t height, uint8_t x, uint8_t y) {
	return true;
}
