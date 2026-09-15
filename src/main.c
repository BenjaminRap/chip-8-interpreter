#include "sdl_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <strings.h>

bool clear_screen(sdl_handler_t* sdl_handler) {
	if (SDL_SetRenderDrawColor(sdl_handler->renderer, 0, 0, 0, 255) < 0
		|| SDL_RenderClear(sdl_handler->renderer) < 0) {
		fprintf(stderr, "%s", SDL_GetError());

		return false;
	}
	SDL_RenderPresent(sdl_handler->renderer);
	return true;
}

int main(void)
{
	sdl_handler_t	sdl_handler;
	bool 			initiated = init_handler(&sdl_handler);

	if (!initiated)
		return EXIT_FAILURE;
	clear_screen(&sdl_handler);
	SDL_Delay(6000);
	clear_handler(&sdl_handler);
    return EXIT_SUCCESS;
}
