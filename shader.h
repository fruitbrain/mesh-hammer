#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
	// The Program ID
	GLuint program;

	// Constructor reads and builds the shader
	Shader(const GLchar* vertex_path, const GLchar* fragment_path)
	{
		/* Read the source code from filePath */
		std::string vertex_source_str;
		std::string fragment_source_str;
		std::ifstream vertex_file;
		std::ifstream fragment_file;
		// ensures ifstream objects can throw exceptions:
		vertex_file.exceptions(std::ifstream::badbit);
		fragment_file.exceptions(std::ifstream::badbit);
		try {
			// Open files
			vertex_file.open(vertex_path);
			fragment_file.open(fragment_path);
			std::stringstream vertex_stream, fragment_stream;
			// Read file's buffer contents into streams
			vertex_stream << vertex_file.rdbuf();
			fragment_stream << fragment_file.rdbuf();
			// close file handlers
			vertex_file.close();
			fragment_file.close();
			// Convert stream into GLchar array
			vertex_source_str = vertex_stream.str();
			fragment_source_str = fragment_stream.str();
		}
		catch(std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const GLchar* vertex_source = vertex_source_str.c_str();
		const GLchar* fragment_source = fragment_source_str.c_str();

		/* Compile shaders */
		GLuint vertex, fragment;
		GLint success;
		GLchar info_log[512];

		// Vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_source, NULL);
		glCompileShader(vertex);
		// Check for compile errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, info_log);
			std::cout << "Error: vertex shader compilation failed: " << info_log << std::endl;
		}

		// Fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_source, NULL);
		glCompileShader(fragment);
		// Check for compile errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, info_log);
			std::cout << "Error: fragment shader compilation failed: " << info_log << std::endl;
		}

		/* Link shaders */
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		// Check for linking errors
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, info_log);
			std::cout << "Error: shader linking failed: " << info_log << std::endl;
		}

		// Discard shaders as they got linked into the program
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// Use the program
	void use()
	{
		glUseProgram(program);
	}
};

#endif
