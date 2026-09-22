#ifndef INTERPRETER_H
# define INTERPRETER_H

# include <stdint.h>
# include "arguments.h"

# define MEMORY_SIZE 4096
# define PROGRAM_ADDRESS 0x200
# define FONTSET_ADDRESS 0x050
# define STACK_SIZE 16
# define DISPLAY_SIZE_X 64
# define DISPLAY_SIZE_Y 32
# define EXTENDED_DISPLAY_SIZE_X 128
# define EXTENDED_DISPLAY_SIZE_Y 64

typedef struct i_display_s {
	bool	(*clear_render)(void* data);
	bool	(*display)(void* data, void* sprite, uint8_t height, uint8_t x, uint8_t y);
	void*	data;
}	i_display_t;

typedef struct interpreter_s {
	void*			memory;
	uint16_t		program_counter;
	uint16_t		stack[STACK_SIZE];
	uint8_t			stack_top;
	uint16_t		index_register;
	uint8_t			registers[16];
	arguments_t*	args;
	i_display_t*	display;
	uint8_t*		screen;
	uint8_t			screen_width;
	uint8_t			screen_height;
} interpreter_t;

bool	init_interpreter(interpreter_t* interpreter, arguments_t* args, i_display_t* display, \
			uint8_t width, uint8_t height);
void	clear_interpreter(interpreter_t* interpreter);

#endif // !INTERPRETER_H
