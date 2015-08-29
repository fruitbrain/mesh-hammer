/**
   Read .plum file and return resulting Mesh struct.
*/
struct Mesh plum_loader(const char* filename);

/**
   Convert .plum file directly into a VBO data array.
*/
float* plum_loader_vbo(const char* filename);
