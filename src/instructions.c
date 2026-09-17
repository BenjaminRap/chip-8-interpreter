#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdint.h>

#include "interpreter.h"

bool	clear_screen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	return true;
}

bool	call_subroutine(interpreter_t *interpreter, uint16_t memory_address) {
	if (memory_address > interpreter->program_size - 4)
		return false;
	interpreter->program_counter = memory_address;
	return true;
}

bool	jump(interpreter_t *interpreter, uint16_t memory_address) {
	if (memory_address > interpreter->program_size - 4)
		return false;
	interpreter->program_counter = memory_address;
	return true;
}
