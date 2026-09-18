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

bool	execute_instruction(const instruction_t instr, interpreter_t* inter);
bool	handle_events(void);

bool	main_loop(interpreter_t* interpreter) {
	while (interpreter->program_counter <= interpreter->program_size - 2) {
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
	interpreter_t	interpreter;

	if (!read_arguments(argc, argv, &interpreter.args))
		return EXIT_FAILURE;

	bool initiated = init_interpreter(&interpreter);

	if (!initiated)
		return EXIT_FAILURE;
	bool success = main_loop(&interpreter);

	clear_interpreter(&interpreter);
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
