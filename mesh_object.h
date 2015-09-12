#include <vector>
#include "model.h"

// GLFW
#include <GLFW/glfw3.h>

class MeshObject : public Model {
public:
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
	/* Normalized face normal array that consists of 3-element coordinate arrays */
	float** normal_array;

	MeshObject();
	~MeshObject();

	void draw() override;
	void create(std::vector<GLfloat> vbo_data);
};
