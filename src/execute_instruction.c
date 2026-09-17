#include "instructions.h"

bool	execute_instruction(const instruction_t instr, interpreter_t* inter) {
	switch (instr.opcode) {
		case 0x0 : {
			if (instr.nnn == 0x0E0)
				return clear_screen(inter->sdl_handler.renderer);
			if (instr.nnn == 0x0EE)
				return return_from_subroutine(inter);
			break;
		}
		case 0x1:
			return jump_to_nnn(inter, instr.nnn);
		case 0x2:
			return call_nnn_subroutine(inter, instr.nnn);
		case 0x3:
			return skip_if_vx_equal_nn(inter, instr.x, instr.nn);
		case 0x4:
			return skip_if_vx_not_equal_nn(inter, instr.x, instr.nn);
		case 0x5:
			return skip_if_vx_equal_vy(inter, instr.x, instr.y);
		case 0x6:
			return set_x_to_nn(inter, instr.x, instr.nn);
		case 0x7:
			return add_nn_to_x_no_carry(inter, instr.x, instr.nn);
		case 0x8:
			switch (instr.n) {
				case 0x0:
					return set_x_to_vy(inter, instr.x, instr.y);
				case 0x1:
					return set_x_to_vx_binary_or_vy(inter, instr.x, instr.y);
				case 0x2:
					return set_x_to_vx_binary_and_vy(inter, instr.x, instr.y);
				case 0x3:
					return set_x_to_vx_binary_xor_vy(inter, instr.x, instr.y);
				case 0x4:
					return set_x_to_vx_plus_vy(inter, instr.x, instr.y);
				case 0x5:
					return set_x_to_vx_minus_vy(inter, instr.x, instr.y);
				case 0x7:
					return set_x_to_vy_minus_vx(inter, instr.x, instr.y);
			}
			break ;
		case 0x9:
			return skip_if_vx_not_equal_vy(inter, instr.x, instr.y);

	}
	uint8_t*	instruction_bytes = (uint8_t*)&instr;

	fprintf( stderr, "Unknown instruction : %X%X\n", instruction_bytes[0], instruction_bytes[1]);
	return false;
}
