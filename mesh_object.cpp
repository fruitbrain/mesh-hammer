#include "mesh_object.h"

MeshObject::MeshObject()
{
}

MeshObject::~MeshObject()
{
	// Deleted in destructor of Model
}

void MeshObject::create(std::vector<GLfloat> vbo_data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	std::cout << "vbo: " << vbo << std::endl;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo_data.size() * sizeof(GLfloat), vbo_data.data(), GL_STATIC_DRAW);

	// Link vertex attributes (Important!)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// (supposedly) unbind GL_ARRAY_BUFFER

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbo_datas.push_back(vbo_data);
}

void MeshObject::draw()
{
	/* Matrices */
	glm::mat4 model;
	model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(75.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	shader->use();
	shader->set_uniform("color_object", 1.0f, 0.5f, 0.31f);
	shader->set_uniform("color_light", 1.0f, 1.0f, 1.0f);
	//shader->set_uniform("pos_light", pos_light.x, pos_light.y, pos_light.z);
	shader->set_uniform("pos_light", 0.7f, 0.7f, 0.7f); // FIXME
	shader->set_uniform("model", model);
	shader->set_uniform("view", view);
	shader->set_uniform("projection", projection);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 72);
	glBindVertexArray(0);
}
