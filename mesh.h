#ifndef _MESH_H_
#define _MESH_H_

// For size_t and bool(C)
#ifdef __cplusplus
#include <cstddef>
#else
#include <stdbool.h>
#include <stddef.h>
#endif

/* C struct representation of the mesh data of an object
   Will be directly converted to and from Racket data */
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
	/* Normalized face normal array that consists of 3-element coordinate arrays */
	float** normal_array;
} Mesh;

#endif
