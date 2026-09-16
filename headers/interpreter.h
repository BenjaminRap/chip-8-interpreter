#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "sdl_handler.h"

# define MEMORY_SIZE 4098
# define MAX_PROGRAM_SIZE 3000

typedef struct interpreter_s {
	sdl_handler_t	sdl_handler;
	char*			memory;
	size_t			program_size;
	size_t			program_counter;
} interpreter_t;

bool	init_interpreter(interpreter_t* interpreter, char* program_size);
void	clear_interpreter(interpreter_t* interpreter);

#endif // !INTERPRETER_H
