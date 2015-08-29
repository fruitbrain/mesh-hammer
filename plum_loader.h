struct Mesh {
	// FIXME: document
	int vertex_count;
	int face_count;
	float* vertex_array;
	int* face_array;

	// Destructor
	~Mesh() {
		std::cout << "Destructing!" << std::endl;
		delete [] vertex_array;
		delete [] face_array;
	}
};

/**
   Read .plum file and return resulting Mesh struct.
*/
struct Mesh plum_loader(const char* filename);

/**
   Convert .plum file directly into a VBO data array.
*/
float* plum_loader_vbo(const char* filename);
