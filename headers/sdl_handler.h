#ifndef SDL_HANDLER_H
# define SDL_HANDLER_H

# include <SDL2/SDL_render.h>
# include <SDL2/SDL_video.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct sdl_handler_s {
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	bool			sdl_initiated;
} sdl_handler_t;

bool	init_sdl_handler(sdl_handler_t* handler, uint8_t width, uint8_t height);
void	clear_sdl_handler(sdl_handler_t* handler);
bool	sdl_clear(sdl_handler_t* handler);
bool	sdl_display(sdl_handler_t* handler, void* sprite, uint8_t height, uint8_t x, uint8_t y);

#endif // !SDL_HANDLER_H
