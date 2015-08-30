#include <stdio.h>
#include "../plum_loader.h"

int main()
{
	struct Mesh mesh = plum_loader("examples/example.plum");

	printf("\n");
	printf("This is a C program loading C++ shared library libplumloader.\n");
	printf("Vertex count: %d\n", mesh.vertex_count);
	printf("Face count: %d\n", mesh.face_count);
	printf("Vertex array:\n");
	for (int i=0; i<mesh.vertex_count; i++) {
		printf("%f ", mesh.vertex_array[i]);
	}
	printf("\n");
	printf("Face array:\n");
	for (int i=0; i<mesh.face_count; i++) {
		printf("%d ", mesh.face_array[i]);
	}
	printf("\n");

	delete_mesh(mesh);
}
