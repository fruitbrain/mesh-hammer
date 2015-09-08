#ifdef __cplusplus
// We may strip these bunch of #include lines when compiling against C,
// because these header files are already compiled and linked into the .so file.
// These are only here to not clutter already long .cpp files anymore with
// #include lines.
#include <iostream>
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

extern "C" {
#endif

#include "mesh.h"

/**
   Initialize everything needed to show a window and an OpenGL context.
*/
void initialize();

int program();

/**
   Draw the Mesh object.
*/
void draw_mesh_real(Mesh* mesh);

#ifdef __cplusplus
}
#endif
