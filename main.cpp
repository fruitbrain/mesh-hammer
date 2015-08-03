#include "display.h"
#include <iostream>

int DISPLAY_WIDTH = 800;
int DISPLAY_HEIGHT = 400;

int main(int argc, char** argv) {

	for (int i=0; i<100; i++)
	{
		Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Hello Minecraft");
	}
	
	std::cout << "New world" << std::endl;
}
