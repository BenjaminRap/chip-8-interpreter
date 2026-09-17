#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# include <SDL2/SDL_render.h>
# include <stdbool.h>

# include "interpreter.h"

# define INSTRUCTION_SIZE 2
# define ADDRESS_SIZE 2

typedef struct instruction_s {
	uint8_t		opcode;
	uint8_t		x;
	uint8_t		y;
	uint8_t		n;
	uint8_t		nn;
	uint16_t	nnn;
}	instruction_t;

instruction_t	extract_instruction(uint16_t data);
bool 			clear_screen(SDL_Renderer *renderer);
bool			call_nnn_subroutine(interpreter_t *interpreter, uint16_t memory_address);
bool			return_from_subroutine(interpreter_t* interpreter);
bool			jump_to_nnn(interpreter_t *interpreter, uint16_t memory_address);
bool			skip_if_vx_equal_nn(interpreter_t* interpreter, \
					uint8_t register_index, uint8_t immediate);
bool			skip_if_vx_not_equal_nn(interpreter_t* interpreter, \
					uint8_t register_index, uint8_t immediate);
bool			skip_if_vx_equal_vy(interpreter_t* interpreter, \
					uint8_t first_register_index, uint8_t second_register_index);
bool			skip_if_vx_not_equal_vy(interpreter_t* interpreter, \
					uint8_t first_register_index, uint8_t second_register_index);
bool			set_x_to_nn(interpreter_t* inter, uint8_t x, uint8_t nn);
bool			add_nn_to_x_no_carry(interpreter_t* inter, uint8_t x, uint8_t nn);
bool			set_x_to_vy(interpreter_t* inter, uint8_t x, uint8_t y);
bool			set_x_to_vx_binary_or_vy(interpreter_t* inter, uint8_t x, uint8_t y);
bool			set_x_to_vx_binary_and_vy(interpreter_t* inter, uint8_t x, uint8_t y);
bool			set_x_to_vx_binary_xor_vy(interpreter_t* inter, uint8_t x, uint8_t y);
bool			set_x_to_vx_plus_vy(interpreter_t* inter, uint8_t x, uint8_t y);
bool			set_x_to_vx_minus_vy(interpreter_t* inter, uint8_t x, uint8_t y);
bool			set_x_to_vy_minus_vx(interpreter_t* inter, uint8_t x, uint8_t y);

#endif // !INSTRUCTIONS_H
