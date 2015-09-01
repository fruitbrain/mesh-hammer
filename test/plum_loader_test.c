#include <stdio.h>
#include "../plum_loader.h"

int main()
{
	struct Mesh mesh = plum_loader("examples/example.plum");

	printf("\n");
	printf("This is a C program loading C++ shared library libplumloader.\n");
	printf("Vertex count: %zu\n", mesh.vertex_count);
	printf("Face count: %zu\n", mesh.face_count);
	printf("Vertex array:\n");
	for (size_t i=0; i<mesh.vertex_count; i++) {
		float* v = mesh.vertex_array[i];
		printf("%f %f %f\n", v[0], v[1], v[2]);
	}
	printf("\n");
	printf("Face array:\n");
	for (size_t i=0; i<mesh.face_count; i++) {
		int size = mesh.face_array[i][0];
		for (int j=0; j<size; j++)
			printf("%d ",mesh.face_array[i][j+1]);
		printf("\n");
	}
	printf("\n");

	delete_mesh(mesh);
}
