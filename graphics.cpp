#include "graphics.h"

void draw_mesh(GLuint vao, Shader* shader);
void draw_lamp(GLuint vao, Shader* shader);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;
glm::vec3 pos_light(1.2f, 1.0f, 2.0f);
const GLuint WIDTH = 800, HEIGHT = 600;

// Cube
GLfloat vertices_cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

/**
   Initialize everything needed to show a window and an OpenGL context.
*/
extern "C" void initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Plum", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}

	glViewport(0, 0, 800, 600);

	/* OpenGL options */
	glEnable(GL_DEPTH_TEST);
}

/**
   Main program flow
*/
extern "C" int program()
{
	initialize();

	/* Load mesh data */
	// Mesh mesh = plum_loader("examples/example.plum");
	std::vector<GLfloat> vbo_vector = vboify(mesh);

	/* Shaders */
	Shader* shader_mesh;
	Shader* shader_lamp;
	shader_mesh = new Shader("shader.vert", "shader.frag");
	shader_lamp = new Shader("shader.vert", "lamp.frag");

	/* Generate Opengl objects */
	GLuint vbo;
	glGenBuffers(1, &vbo);
	GLuint vbo_cube;
	glGenBuffers(1, &vbo_cube);

	/* VAO for the mesh */
	GLuint vao_mesh;
	glGenVertexArrays(1, &vao_mesh);
	glBindVertexArray(vao_mesh);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo_vector.size() * sizeof(GLfloat), vbo_vector.data(), GL_STATIC_DRAW);

	// Link vertex attributes (Important!)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// Is this needed?

	glBindVertexArray(0);

	/* VAO for the light */
	GLuint vao_light;
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	/* Render loop */
	while (!glfwWindowShouldClose(window)) {
		/* Check and call events */
		glfwPollEvents();

		/* Render */
		// Reset screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_mesh(vao_mesh, shader_mesh);
		draw_lamp(vao_light, shader_lamp);

		/* Swap the buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	delete shader_mesh;
	delete shader_lamp;

	return 0;
}

/**
   Single draw call for the mesh.
*/
void draw_mesh(GLuint vao, Shader* shader)
{
	/* Matrices */
	glm::mat4 model;
	model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(75.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	shader->use();
	shader->set_uniform("color_object", 1.0f, 0.5f, 0.31f);
	shader->set_uniform("color_light", 1.0f, 1.0f, 1.0f);
	shader->set_uniform("pos_light", pos_light.x, pos_light.y, pos_light.z);
	shader->set_uniform("model", model);
	shader->set_uniform("view", view);
	shader->set_uniform("projection", projection);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 72);
	glBindVertexArray(0);
}

/**
   Single draw call for the lamp.
*/
void draw_lamp(GLuint vao, Shader* shader)
{
	glm::mat4 model;
	model = glm::translate(model, pos_light);
	model = glm::scale(model, glm::vec3(0.2f));
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(75.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	shader->use();
	shader->set_uniform("model", model);
	shader->set_uniform("view", view);
	shader->set_uniform("projection", projection);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

// Seems like returning vector by value doesn't affect performance, the compiler
// does the optimization work.
std::vector<GLfloat> vboify(const Mesh mesh)
{
	std::vector<GLfloat> vbo;
	for (std::size_t i = 0; i < mesh.face_count; i++) {
		std::vector<int> face = get_face(mesh, i);
		for (std::vector<int>::iterator it = face.begin(); it != face.end(); it++) {
			std::vector<GLfloat> found_vertex = get_vertex(mesh, *it);
			vbo.insert(vbo.end(), found_vertex.begin(), found_vertex.end());
		}
	}

	// Print vbo (for debugging)
	std::cout << "Printing VBO array:" << std::endl;
	for (auto it = vbo.begin(); it != vbo.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	return vbo;
}

/**
   Key callback function for GLFW.
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
