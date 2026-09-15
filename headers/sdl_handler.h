#ifndef SDL_HANDLER_H
# define SDL_HANDLER_H

# include <SDL2/SDL_render.h>
# include <SDL2/SDL_video.h>
# include <stdbool.h>

# define DISPLAY_SIZE_X 64
# define DISPLAY_SIZE_Y 32

typedef struct sdl_handler_s {
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	bool			sdl_initiated;

} sdl_handler_t;

bool	init_handler(sdl_handler_t* handler);
void	clear_handler(sdl_handler_t* handler);

#endif // !SDL_HANDLER_H
