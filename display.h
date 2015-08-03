#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <string>

class Display
{

public:

	// ctor
	Display(int width, int height, const std::string& title);
	
	void Clear(float r, float g, float b, float a);
	void Update();
	void IsClosed();

	// dtor
	virtual ~Display();

protected:
private:
	
};
