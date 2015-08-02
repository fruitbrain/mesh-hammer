#include "sdl.hpp"

SDL_Window* win;
SDL_Renderer* ren;

int sdl_init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
	 	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	 	return 1;
	}
	std::cout << "Wow" << std::endl;
	return 0;
}

int sdl_window() {
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
}

int sdl_renderer() {
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
}

int sdl_cleanup() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
