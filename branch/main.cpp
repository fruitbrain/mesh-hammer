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
	
	GLfloat tripoints[] = {
		0.0f,	0.5f,	0.0f,
		0.5f,	-0.5f,	0.0f,
		-0.5f,	-0.5f,	0.0f,
	};
	
	// Vertex array Buffer Object
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tripoints), tripoints, GL_STATIC_DRAW);
	
	// Vertex array Attribute Object
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	// Shader
	const char* vertex_shader = 
	"#version 420\n"
	"in vec3 vp;"
	"void main(){"
	"	gl_Position = vec4(vp, 1.0);"
	"}";
	
	const char* fragment_shader = 
	"#version 420\n"
	"out vec4 frag_colour;"
	"void main(){"
	"	frag_colour = vec4(0.5,0.0,0.5,1.0);"
	"}";
	
	// Compiling Shader
	
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	
	// Creating a 'program' to attatch & link the shaders together
	
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	
	// Drawing
	
	while(!glfwWindowShouldClose(window)){
		//wiping the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		
		// draw the points & update
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	// close GL context and GLFW resources
	glfwTerminate();
	return 0;
}