#ifdef __cplusplus
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
