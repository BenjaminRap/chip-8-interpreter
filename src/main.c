#include "interpreter.h"
#include "sdl_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
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

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments, expected one, the program to run.");
		return EXIT_FAILURE;
	}
	interpreter_t	interpreter;

	bool initiated = init_interpreter(&interpreter, argv[1]);

	if (!initiated)
		return EXIT_FAILURE;
	fwrite(interpreter.memory, sizeof(char), interpreter.program_size, stdout);
	clear_screen(&interpreter.sdl_handler);
	SDL_Delay(3000);
	clear_interpreter(&interpreter);
    return EXIT_SUCCESS;
}
