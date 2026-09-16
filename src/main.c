#include "interpreter.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <strings.h>

bool	handle_events(void) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}

void	execute_instruction(const char* instruction) {
	fwrite(instruction, 1, 4, stdout);
}

void	main_loop(interpreter_t* interpreter) {
	while (interpreter->program_counter <= interpreter->program_size - 4) {
		if (!handle_events())
			return ;
		const char* current_instruction = interpreter->memory + interpreter->program_counter;

		execute_instruction(current_instruction);
		interpreter->program_counter += 4;
        SDL_RenderPresent(interpreter->sdl_handler.renderer);
		SDL_Delay(16);
	}
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
	SDL_SetRenderDrawColor(interpreter.sdl_handler.renderer, 0, 0, 0, 255);
	main_loop(&interpreter);
	clear_interpreter(&interpreter);
    return EXIT_SUCCESS;
}
