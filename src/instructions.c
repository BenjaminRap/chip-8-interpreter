#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdint.h>

#include "instructions.h"
#include "interpreter.h"

instruction_t		extract_data(uint16_t data) {
	instruction_t	instruction;

	instruction.opcode = data >> 12;
	instruction.x = data >> 8 & 0x000F;
	instruction.y = data >> 4 & 0x000F;
	instruction.nnn = data & 0x0FFF;
	instruction.nn = data & 0x00FF;
	instruction.n = data & 0x000F;
	return instruction;
}

bool	clear_screen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	return true;
}

bool	return_from_subroutine(interpreter_t* inter) {
	if (inter->stack_size == 0) {
		fprintf(stderr, "Trying to return from an nonexistant subroutine !");
		return false;
	}
	inter->stack_size -= ADDRESS_SIZE;
	uint16_t	stack_top = inter->stack_size + inter->program_size;
	uint16_t	memory_address = *(uint16_t*)(inter->memory + stack_top);

	inter->program_counter = memory_address;
	return true;
}

bool	call_nnn_subroutine(interpreter_t *inter, uint16_t nnn) {
	if (nnn > inter->program_size - INSTRUCTION_SIZE) {
		fprintf(stderr, "Tried to call an invalid subroutine, address : %d !", nnn);
		return false;
	}
	uint16_t	stack_top = inter->stack_size + inter->program_size;

	if (stack_top > MEMORY_SIZE - ADDRESS_SIZE) {
		fprintf(stderr, "No more room on the stack !");
		return false;
	}
	*(uint16_t*)(inter->memory + stack_top) = inter->program_counter + INSTRUCTION_SIZE;
	inter->stack_size += ADDRESS_SIZE;
	inter->program_counter = nnn;
	return true;
}

bool	jump_to_nnn(interpreter_t *inter, uint16_t nnn) {
	if (nnn > inter->program_size - INSTRUCTION_SIZE) {
		fprintf(stderr, "Tried to jump to an invalid memory address : %d !", nnn);
		return false;
	}
	inter->program_counter = nnn;
	return true;
}

bool	skip_if_vx_equal_nn(interpreter_t* inter, uint8_t x, uint8_t nn) {
	if (inter->registers[x] == nn)
		inter->program_counter += INSTRUCTION_SIZE;
	return true;
}

bool	skip_if_vx_not_equal_nn(interpreter_t* interpreter, uint8_t x, uint8_t nn) {
	if (interpreter->registers[x] != nn)
		interpreter->program_counter += INSTRUCTION_SIZE;
	return true;
}

bool	skip_if_vx_equal_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	if (inter->registers[x] == inter->registers[y])
		inter->program_counter += INSTRUCTION_SIZE;
	return true;
}

bool	skip_if_vx_not_equal_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	if (inter->registers[x] != inter->registers[y])
		inter->program_counter += INSTRUCTION_SIZE;
	return true;
}

bool	set_x_to_nn(interpreter_t* inter, uint8_t x, uint8_t nn) {
	inter->registers[x] = nn;
	return true;
}

bool	add_nn_to_x_no_carry(interpreter_t* inter, uint8_t x, uint8_t nn) {
	inter->registers[x] = inter->registers[x] + nn;
	return true;
}

bool	set_x_to_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	inter->registers[x] = inter->registers[y];
	return true;
}

bool	set_x_to_vx_binary_or_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	inter->registers[x] = inter->registers[y] | inter->registers[x];
	return true;
}

bool	set_x_to_vx_binary_and_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	inter->registers[x] = inter->registers[y] & inter->registers[x];
	return true;
}

bool	set_x_to_vx_binary_xor_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	inter->registers[x] = inter->registers[y] ^ inter->registers[x];
	return true;
}

bool	set_x_to_vx_plus_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	uint8_t	vx = inter->registers[x];
	uint8_t	vy = inter->registers[y];

	if (vx > 255 - vy)
		inter->registers[15] = 1;
	else
		inter->registers[15] = 0;
	inter->registers[x] = vx + vy;
	return true;
}

bool	set_x_to_vx_minus_vy(interpreter_t* inter, uint8_t x, uint8_t y) {
	uint8_t	vx = inter->registers[x];
	uint8_t	vy = inter->registers[y];

	if (vx >= vy)
		inter->registers[15] = 1;
	else
		inter->registers[15] = 0;
	inter->registers[x] = vx - vy;
	return true;
}

bool	set_x_to_vy_minus_vx(interpreter_t* inter, uint8_t x, uint8_t y) {
	uint8_t	vx = inter->registers[x];
	uint8_t	vy = inter->registers[y];

	if (vy >= vx)
		inter->registers[15] = 1;
	else
		inter->registers[15] = 0;
	inter->registers[x] = vy - vx;
	return true;
}
