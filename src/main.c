#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "arguments.h"
#include "interpreter.h"
#include "instructions.h"
#include "sdl_handler.h"

bool	execute_instruction(const instruction_t instr, interpreter_t* inter);
bool	handle_events(void);

bool	main_loop(interpreter_t* interpreter) {
	while (interpreter->program_counter <= MEMORY_SIZE - INSTRUCTION_SIZE) {
		if (!handle_events())
			return true;
		const uint16_t* data = interpreter->memory + interpreter->program_counter;
		const instruction_t instruction = extract_instruction(*data);

		if (execute_instruction(instruction, interpreter))
			return false;
		interpreter->program_counter += INSTRUCTION_SIZE;
		SDL_Delay(16);
	}
	return true;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	arguments_t		args;

	if (!read_arguments(argc, argv, &args))
		return EXIT_FAILURE;
	bool	extended = args.extension == EXTENSION_SUPER_CHIP;
	uint8_t	width = extended ? EXTENDED_DISPLAY_SIZE_X : DISPLAY_SIZE_X;
	uint8_t	height = extended ? EXTENDED_DISPLAY_SIZE_Y : DISPLAY_SIZE_Y;
	sdl_handler_t	display;

	bool	sdl_initiated = init_sdl_handler(&display, width, height);

	if (!sdl_initiated)
		return EXIT_FAILURE;
	i_display_t	display_interface;

	display_interface.data = &display;
	display_interface.display = (typeof(display_interface.display))sdl_display;
	display_interface.clear_render = (typeof(display_interface.clear_render))sdl_clear;
	interpreter_t	interpreter;

	bool initiated = init_interpreter(&interpreter, &args, &display_interface, width, height);

	if (!initiated) {
		clear_sdl_handler(&display);
		return EXIT_FAILURE;
	}
	bool success = main_loop(&interpreter);

	clear_interpreter(&interpreter);
	clear_sdl_handler(&display);
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
