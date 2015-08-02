#include "sdl.hpp"

int main(int argc, char** argv) {
	sdl_init();
	sdl_window();
	sdl_renderer();
	sdl_cleanup();
	return 0;
}
