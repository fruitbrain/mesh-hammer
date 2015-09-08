#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "plum_loader.h"

float char_vector_to_float(std::vector<char> charvec);
int char_vector_to_int(std::vector<char> charvec);

/**
   Read .plum file and return resulting Mesh struct.
*/
extern "C" Mesh plum_loader(const char* filename)
{
	// open an input stream for the file for vertex data collection
	std::ifstream ifs(filename, std::ios::in);

	if(!ifs.is_open()) {
		std::cerr << "ERROR : The file did not open." << std::endl;

		/* Return fake empty struct just to bail out */
		Mesh mesh;
		mesh.read_status = false;
		return mesh;
	}

	// vertex container for all of the vertex data
	std::vector<std::vector<float> > vc;
	// facial vertex container for all of the VBO data
	std::vector<std::vector<int> > fc;

	// start a loop to find all the vertex data & store it in vc
	char memblock[1];

	std::cout << "File content:" << std::endl;
	while(true) {
		ifs.read(memblock, 1);

		if(memblock[0] == 'v') {		// Vertex line
			std::vector<float> vertex;
			std::vector<char> tempvec;
			ifs.seekg(1, std::ios::cur);

			while (true) {
				ifs.read(memblock, 1);

				// 0x20: space, 0x0d: newline
				if (memblock[0] != 0x20 && memblock[0] != 0x0a) {
					/* Reading 1 coord */
					tempvec.push_back(memblock[0]);
					std::cout << memblock[0];
				} else if (memblock[0] == 0x20) {
					/* Finished 1 coord */
					vertex.push_back(char_vector_to_float(tempvec));
					tempvec.clear();
					std::cout << " ";
				} else {
					/* Finished 1 line */
					vertex.push_back(char_vector_to_float(tempvec));
					vc.push_back(vertex);
					tempvec.clear();
					std::cout << std::endl;

					//ifs.seekg(1, std::ios::cur);
					break;
				}
			}
		} else if (memblock[0] == 'f') {	// Face line
			std::vector<int> face;
			std::vector<char> tempvec;
			ifs.seekg(1, std::ios::cur);

			while (true) {
				ifs.read(memblock, 1);

				// 0x20: space, 0x0d: newline
				if(memblock[0] != 0x20 && memblock[0] != 0x0a) {
					/* Reading 1 index */
					tempvec.push_back(memblock[0]);
					std::cout << memblock[0];
				} else if(memblock[0] == 0x20) {
					/* Finished 1 index */
					face.push_back(char_vector_to_int(tempvec));
					tempvec.clear();
					std::cout << " ";
				} else {
					/* Finished 1 line */
					face.push_back(char_vector_to_int(tempvec));
					fc.push_back(face);
					tempvec.clear();
					std::cout << std::endl;

					//ifs.seekg(1, std::ios::cur);
					break;
				}
			}
		} else { 		// Nothing to read, skip to the next line
			while (memblock[0] != 0x0a)
				ifs.read(memblock, 1);
			if (ifs.eof())
				break;
			//ifs.seekg(1, std::ios::cur);
		}
	}
	std::cout << std::endl;
	ifs.close();

	// Convert vc and fc into float and int array
	float** vertex_array = new float*[fc.size()];
	for (std::size_t i=0; i<vc.size(); i++) {
		vertex_array[i] = new float[3];
		vertex_array[i][0] = vc[i][0];
		vertex_array[i][1] = vc[i][1];
		vertex_array[i][2] = vc[i][2];
	}

	// Caution: 0th element is the *size of that array*
	int** face_array = new int*[fc.size()];
	for (std::size_t i=0; i<fc.size(); i++) {
		face_array[i] = new int[1+fc[i].size()];
		face_array[i][0] = fc[i].size();
		for (std::size_t j=0; j<fc[i].size(); j++)
			face_array[i][j+1] = fc[i][j];
	}

	// Print arrays for debugging purpose
	std::cout << "vertex_array:" << std::endl;
	for (std::size_t i=0; i<vc.size(); i++) {
		std::cout << vertex_array[i][0] << " ";
		std::cout << vertex_array[i][1] << " ";
		std::cout << vertex_array[i][2] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "face_array:" << std::endl;
	for (std::size_t i=0; i<fc.size(); i++) {
		int size = face_array[i][0];
		for (int j=0; j<size; j++)
			std::cout << face_array[i][j+1] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Mesh data loading completed" << std::endl;

	// Pack the results into a struct.
	Mesh mesh;
	mesh.read_status = true;
	mesh.vertex_count = vc.size();
	mesh.face_count = fc.size();
	mesh.vertex_array = vertex_array;
	mesh.face_array = face_array;

	return mesh;
}

/**
   Convert .plum file directly into a VBO data array.
*/
extern "C" GLfloat* plum_loader_vbo(const char* filename)
{
	Mesh mesh = plum_loader(filename);
	const int vbo_size = mesh.face_count * 3;
	GLfloat* vbo_list = new GLfloat[vbo_size];

	// FIXME
	/*for (int i=0; i<mesh.face_count; i++) {
		vbo_list[i*3] = mesh.vertex_array[mesh.face_array[i][0]] [0];
		vbo_list[i*3+1] = mesh.vertex_array[mesh.face_array[i][1]] [1];
		vbo_list[i*3+2] = mesh.vertex_array[mesh.face_array[i][2]] [2];
		}*/

	// Delete arrays of struct mesh
	delete_mesh(mesh);

	// Print VBOList items
	std::cout << "Printing vbo_list[]..." << std::endl;
	for (int i=0; i<vbo_size; i++)
		std::cout << vbo_list[i] << " ";
	std::cout << std::endl;

	return vbo_list;
}

/**
   Explicit destructor for struct Mesh.
   This is needed because C doensn't support destructors.
*/
extern "C" void delete_mesh(Mesh mesh)
{
	std::cout << "Deleting Mesh..." << std::endl;
	for (std::size_t i=0; i<mesh.vertex_count; i++)
		delete [] mesh.vertex_array[i];
	delete [] mesh.vertex_array;
	for (std::size_t i=0; i<mesh.face_count; i++)
		delete [] mesh.face_array[i];
	delete [] mesh.face_array;
}

extern "C" void array_test(float** arr)
{
	std::cout << arr[0][0] << arr[0][1] << std::endl;
	std::cout << arr[1][0] << arr[1][1] << std::endl;
}

extern "C" float* array_return_1d()
{
	float* arr = new float[3];
	arr[0] = 0.0;
	arr[1] = 1.0;
	arr[2] = 2.0;
	return arr;
}

extern "C" float** array_return_2d()
{
	float** arr = new float*[2];
	for (int i=0; i<2; i++) {
		arr[i] = new float[3];
	}
	return arr;
}

/**
   Convert vector<char> to float and return it.
*/
float char_vector_to_float(std::vector<char> charvec)
{
	std::string str(charvec.begin(), charvec.end());
	return std::stof(str);
}

/**
   Convert vector<char> to int and return it.
*/
int char_vector_to_int(std::vector<char> charvec)
{
	std::string str(charvec.begin(), charvec.end());
	return std::stoi(str);
}
