#include "interpreter.h"
#include "sdl_handler.h"

static bool read_program_file(interpreter_t* interpreter, FILE* program_file) {
	if (fseek(program_file, 0, SEEK_END))
		goto error;

	long	program_size = ftell(program_file);

	if (program_size <= 0)
		goto error;
	interpreter->program_size = (size_t)program_size;
	if (program_size > MAX_PROGRAM_SIZE) {
		fprintf(stderr, "The program size is too big, maximum is %d", MAX_PROGRAM_SIZE);
		return false;
	}
	rewind(program_file);
	size_t readden = fread(interpreter->memory, 1, program_size, program_file);

	if (readden != interpreter->program_size)
		goto error;
	return true;
error:
	perror("Error reading the program file.");
	return false;
}

bool read_program(interpreter_t* interpreter, char *program_file) {
	FILE*	file = fopen(program_file, "r");

	if (file == NULL) {
		perror("Error reading the program file.");

		return false;
	}
	bool err = read_program_file(interpreter, file);

	fclose(file);
	return err;
}

bool	init_interpreter(interpreter_t* interpreter, char *program_file) {
	bzero(interpreter, sizeof(interpreter_t));

	interpreter->memory = malloc(MEMORY_SIZE);
	if (!interpreter->memory
		|| !read_program(interpreter, program_file)
		|| !init_handler(&interpreter->sdl_handler)) {
		clear_interpreter(interpreter);
		return false;
	}
	return true;
}

void clear_interpreter(interpreter_t* interpreter) {
	if (!interpreter)
		return ;
	clear_handler(&interpreter->sdl_handler);
	if (interpreter->memory)
		free(interpreter->memory);
	bzero(interpreter, sizeof(interpreter_t));
}
