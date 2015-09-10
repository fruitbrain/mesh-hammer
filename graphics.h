#ifdef __cplusplus
// We may strip these bunch of #include lines when compiling against C,
// because these header files are already compiled and linked into the .so file.
// These are only here to not clutter already long .cpp files anymore with
// #include lines.
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "plum_loader.h"

/**
   Struct that contains GLFW window and event queue.
*/
struct Context {
	GLFWwindow* window;
	std::queue<const char*> event_queue;
};

/**
   Process the content of Mesh struct into a giant VBO-ready vector.
*/
std::vector<GLfloat> vboify(const Mesh mesh);

extern "C" {
#endif

#include "mesh.h"

/// For use in Racket
struct Context;
typedef struct Context Context;
typedef const char* Event;

/**
   Initialize everything needed to show a window and an OpenGL context.
*/
Context* initialize();

int program();

/**
   Draw the Mesh object.
*/
void draw_mesh_real(Mesh mesh);

/**
   Pop the first event stored in the event_queue.
*/
Event poll_event(Context* context);

#ifdef __cplusplus
}
#endif
