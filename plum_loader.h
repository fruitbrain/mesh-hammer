#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Include GL headers
#define GLEW_STATIC
#include <GL/glew.h>

typedef struct Mesh {
	/* File read status */
	bool read_status;
	/* Total num of vertices */
	size_t vertex_count;
	/* Total num of faces */
	size_t face_count;
	/* Vertex array that consists of 3-element coordinate arrays */
	float** vertex_array;
	/* Face array that consists of n-element vertex index arrays */
	int** face_array;
} Mesh;

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

#ifdef __cplusplus
}
#endif
