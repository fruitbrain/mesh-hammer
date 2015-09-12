#pragma once
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class Model
{
public:
	Model();
	virtual ~Model();

	virtual void draw();
	virtual void update();
	virtual void set_shader(Shader* shader);
	virtual void destroy();
 
	virtual GLuint get_vao() const;
	virtual std::vector<GLuint> const& get_vbos() const;
 
protected:
	GLuint vao;
	Shader* shader;
	std::vector<GLuint> vbos;
	std::vector<std::vector<GLfloat>> vbo_datas;
};
