#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# include <SDL2/SDL_render.h>
# include <stdbool.h>

typedef struct instruction_s {
	unsigned int opcode : 4;
	union {
		struct {
			unsigned int x : 4;
			unsigned int y : 4;
			unsigned int n : 4;
		} xyn;
		struct {
			unsigned int x : 4;
			unsigned int nn : 8;
		} xnn;
		unsigned int nnn : 12;
	};
} instruction_t;

bool	clear_screen(SDL_Renderer* renderer);
bool	call_subroutine();
bool	jump();

#endif // !INSTRUCTIONS_H
