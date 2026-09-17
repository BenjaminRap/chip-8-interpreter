#include <SDL2/SDL_events.h>
#include <stdbool.h>

bool	handle_events(void) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}
