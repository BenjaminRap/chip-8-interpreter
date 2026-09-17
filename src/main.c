#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <stdio.h>
#include <strings.h>

#include "interpreter.h"
#include "instructions.h"

bool	handle_events(void) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}

bool	execute_instruction(const instruction_t instruction, interpreter_t* interpreter) {
	switch (instruction.opcode) {
		case 0x0:
			if (instruction.nnn == 0x0E0)
				return clear_screen(interpreter->sdl_handler.renderer);
			if (instruction.nnn == 0x0EE)
				return call_subroutine();
			break;
		case 0x1:
			return jump();
			break;
	}
	uint8_t*	instruction_bytes = (uint8_t*)&instruction;

	fprintf( stderr, "Unknown instruction : %X%X", instruction_bytes[0], instruction_bytes[1]);
	return false;
}

bool	main_loop(interpreter_t* interpreter) {
	while (interpreter->program_counter <= interpreter->program_size - 2) {
		if (!handle_events())
			return true;
		const instruction_t current_instruction = *(instruction_t*)(interpreter->memory + interpreter->program_counter);

		if (execute_instruction(current_instruction, interpreter))
			return false;
		interpreter->program_counter += 2;
		SDL_Delay(16);
	}
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
	bool success = main_loop(&interpreter);

	clear_interpreter(&interpreter);
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
