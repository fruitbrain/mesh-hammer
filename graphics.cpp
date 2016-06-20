#include "graphics.h"

void clear_screen();
GLuint make_vao(GLuint vbo, std::vector<GLfloat>& vbo_vector);
GLuint make_vao_mesh(std::vector<GLfloat>& vbo_data);
GLuint make_vao_light(std::vector<GLfloat>& vbo_data);
void draw_mesh(GLuint vao, Shader* shader);
void draw_lamp(GLuint vao, Shader* shader);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

glm::vec3 pos_light(0.8f, 0.8f, 0.8f);
const GLuint WIDTH = 800, HEIGHT = 600;

std::queue<Event>* event_queue;

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
extern "C" Context* initialize()
{
	Context* context = new Context();
	event_queue = &context->event_queue;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	context->window = glfwCreateWindow(WIDTH, HEIGHT, "Plum", nullptr, nullptr);
	if (context->window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(context->window);

	glfwSetKeyCallback(context->window, key_callback);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return nullptr;
	}

	glViewport(0, 0, 800, 600);

	/* OpenGL options */
	glEnable(GL_DEPTH_TEST);

	std::cout << "Context initialized" << std::endl;
	return context;
}

/**
   Main program flow
*/
extern "C" int program()
{
	Context* context = initialize();

	/* Load mesh data */
	Mesh mesh_data = plum_loader("examples/example.plum");
	std::vector<GLfloat> vbo_vector_cube(vertices_cube, vertices_cube + sizeof vertices_cube / sizeof vertices_cube[0]);

	/* Generate VAOs */
	MeshObject mesh_obj(vboify(mesh_data));
	GLuint vao_light = make_vao_light(vbo_vector_cube);

	/* Shaders */
	Shader* shader_lamp;
	shader_lamp = new Shader("shader.vert", "lamp.frag");

	/* Render loop */
	while (!glfwWindowShouldClose(context->window)) {
		/* Check and call events */
		poll_events();

		/* Render */
		clear_screen();

		mesh_obj.draw();
		draw_lamp(vao_light, shader_lamp);

		/* Swap the buffers */
		swap_buffers(context);
	}

	glfwTerminate();	// (supposedly) deletes *window

	delete_mesh(mesh_data);
	delete context;		// (supposedly) deletes event_queue
	delete shader_lamp;

	return 0;
}

GLuint make_vao_mesh(std::vector<GLfloat>& vbo_data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	std::cout << "vbo: " << vbo << std::endl;

	GLuint vao_mesh;
	glGenVertexArrays(1, &vao_mesh);
	glBindVertexArray(vao_mesh);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo_data.size() * sizeof(GLfloat), vbo_data.data(), GL_STATIC_DRAW);

	// Link vertex attributes (Important!)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// (supposedly) unbind GL_ARRAY_BUFFER

	glBindVertexArray(0);

	return vao_mesh;
}

GLuint make_vao_light(std::vector<GLfloat>& vbo_data)
{
	GLuint vbo_cube;
	glGenBuffers(1, &vbo_cube);
	std::cout << "vbo_cube: " << vbo_cube << std::endl;

	GLuint vao_light;
	glGenVertexArrays(1, &vao_light);
	glBindVertexArray(vao_light);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return vao_light;
}

GLuint make_vao(GLuint vbo, std::vector<GLfloat>& vbo_data)
{
	/* VAO for the mesh */
	GLuint vao_mesh;
	glGenVertexArrays(1, &vao_mesh);
	glBindVertexArray(vao_mesh);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo_data.size() * sizeof(GLfloat), vbo_data.data(), GL_STATIC_DRAW);

	// Link vertex attributes (Important!)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// (supposedly) unbind GL_ARRAY_BUFFER

	glBindVertexArray(0);

	return vao_mesh;
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

extern "C" void clear_screen()
{
	// Reset screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern "C" Event probe_event(Context* context)
{
	// Segfaults if pop an empty queue
	if (context->event_queue.size() == 0) {
		return NO_EVENT;
	}
	else {
		Event next_event = context->event_queue.front(); // XXX: might cause memory failure
		context->event_queue.pop();
		return next_event;
	}
}

extern "C" void poll_events()
{
	glfwPollEvents();
}

extern "C" void swap_buffers(Context* context)
{
	// Swap the buffers
	glfwSwapBuffers(context->window);
}

extern "C" bool window_should_close(Context* context)
{
	return glfwWindowShouldClose(context->window) == GL_TRUE;
}

extern "C" void set_window_should_close(Context* context, bool value)
{
	int value_i = value ? GL_TRUE : GL_FALSE;
	glfwSetWindowShouldClose(context->window, value_i);
}

/**
   Key callback function for GLFW.
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		event_queue->push(KEY_ESCAPE);
	}
}
