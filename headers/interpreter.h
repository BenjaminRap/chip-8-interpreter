#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "arguments.h"
# include "sdl_handler.h"

# define MEMORY_SIZE 4098
# define MAX_PROGRAM_SIZE 3000

typedef struct interpreter_s {
	sdl_handler_t	sdl_handler;
	void*			memory;
	uint16_t		program_size;
	uint16_t		program_counter;
	uint16_t		stack_size;
	uint16_t		index_register;
	uint8_t			registers[16];
	arguments_t		args;
} interpreter_t;

bool	init_interpreter(interpreter_t* interpreter);
void	clear_interpreter(interpreter_t* interpreter);

#endif // !INTERPRETER_H
