#include "model.h"

Model::Model() {}

Model::~Model()
{
	destroy();
}

void Model::draw()
{
	// To be overridden
}

void Model::update()
{
	// To be overridden
}

void Model::set_shader(Shader* shader)
{
	this->shader = shader;
}

void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}
 
GLuint Model::get_vao() const
{
	return vao;
}

std::vector<GLuint> const& Model::get_vbos() const
{
	return vbos;
}
