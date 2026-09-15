#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define DISPLAY_SIZE_X 64
#define DISPLAY_SIZE_Y 32

int main(void)
{
    int error = SDL_Init(SDL_INIT_VIDEO);

	if (error != 0) {
		const char* error_msg = SDL_GetError();

		fprintf(stderr, "Error while initializing the sdl : '%s'", error_msg);
		return EXIT_FAILURE;
	}
	SDL_Window* window = SDL_CreateWindow("chip-8", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, DISPLAY_SIZE_X, DISPLAY_SIZE_Y,
			SDL_WINDOW_MAXIMIZED);

	if (window == NULL) {
		const char* error_msg = SDL_GetError();

		fprintf(stderr, "Error while creating the window : '%s'", error_msg);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	if (renderer == NULL) {
		const char* error_msg = SDL_GetError();

		fprintf(stderr, "Error while creating the renderer : '%s'", error_msg);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	SDL_Delay(3000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
    return EXIT_SUCCESS;
}
