#ifdef __cplusplus
extern "C" {
#endif

// Include GL headers
#define GLEW_STATIC
#include <GL/glew.h>
#include "mesh.h"	

/**
   Read .plum file and return resulting Mesh struct.
*/
Mesh plum_loader(const char* filename);

/**
   Convert .plum file directly into a VBO data array.
*/
GLfloat* plum_loader_vbo(const char* filename);

/**
   Explicit destructor for struct Mesh.
   This is needed because C doensn't support destructors.
*/
void delete_mesh(Mesh mesh);

void array_test(float** arr);

float* array_return_1d();
float** array_return_2d();

#ifdef __cplusplus
}
#endif
