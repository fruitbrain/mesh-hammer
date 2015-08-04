#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char** argv)
{
	if(!glfwInit()) // initiate GLFW *activated when GLFW is not initiated
	{
		std::cerr << "ERROR : could not start GLFW!" << std::endl;
		return 1;
	}
	
	// create a GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft", NULL, NULL);
	std::cout << "Created a GLFW window!" << std::endl;
	
	if(!window) // *activated when window is not open
	{
		std::cerr << "ERROR : could not open window with GLFW!" << std::endl;
		glfwTerminate();
		return 1;
	}
	
	glfwMakeContextCurrent(window);
	
	// initiate GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	
	// get OpenGL renderer & version info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderer : " << renderer << std::endl;
	std::cout << "OpenGL Version Supported : " << version << std::endl;
	
	GLfloat points[] = {
		0.0f,	0.5f,	0.0f,
		0.5f,	-0.5f,	0.0f,
		-0.5f,	0.5f,	0.0f,
	};
	
	// Vertex Buffer Object
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	// close GL context and GLFW resources
	glfwTerminate();
	return 0;
}