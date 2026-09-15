#include "sdl_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <strings.h>

int main(void)
{
	sdl_handler_t	sdl_handler;
	bool 			initiated = init_handler(&sdl_handler);

	if (!initiated)
		return EXIT_FAILURE;
	SDL_Delay(3000);
	clear_handler(&sdl_handler);
    return EXIT_SUCCESS;
}
