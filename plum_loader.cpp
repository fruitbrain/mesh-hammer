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
struct Mesh plum_loader(const char* filename)
{
	// open an input stream for the file for vertex data collection
	std::cout << "opening an input stream for the file" << std::endl;
	std::ifstream ifs(filename, std::ios::in|std::ios::binary);

	if(!ifs.is_open())
		std::cerr << "ERROR : The file did not open." << std::endl;

	std::cout << "The file opened successfully." << std::endl;
	std::cout << "Reading data from file to a container..." << std::endl;

	// vertex container for all of the vertex data
	std::vector<std::vector<char> > vc;
	// facial vertex container for all of the VBO data
	std::vector<std::vector<char> > fc;

	// start a loop to find all the vertex data & store it in vc
	char memblock[1];

	while(true) {
		// only used inside while loop, so declare here
		std::vector<char> tempvec;

		ifs.read(memblock, 1);

		if(memblock[0] == 'v') {		// Vertex line
			ifs.seekg(1, std::ios::cur);

			while (true) {
				ifs.read(memblock, 1);

				// 0x20: space, 0x0d: newline
				if (memblock[0] != 0x20 && memblock[0] != 0x0d) {
					std::cout << memblock[0];
					tempvec.push_back(memblock[0]);
				} else if (memblock[0] == 0x20) {
					vc.push_back(tempvec);
					tempvec.clear();
					std::cout << " ";
				} else {
					vc.push_back(tempvec);
					tempvec.clear();
					ifs.seekg(1, std::ios::cur);
					std::cout << std::endl;
					break;
				}
			}
		} else if (memblock[0] == 'f') {	// Face line
			ifs.seekg(1, std::ios::cur);

			while (true) {
				ifs.read(memblock, 1);

				// 0x20: space, 0x0d: newline
				if(memblock[0] != 0x20 && memblock[0] != 0x0d) {
					std::cout << memblock[0];
					tempvec.push_back(memblock[0]);
				} else if(memblock[0] == 0x20) {
					fc.push_back(tempvec);
					tempvec.clear();
					std::cout << " ";
				} else {
					fc.push_back(tempvec);
					tempvec.clear();
					ifs.seekg(1, std::ios::cur);
					std::cout << std::endl;
					break;
				}
			}
		} else { 		// Nothing to read, skip to the next line
			while (memblock[0] != 0x0d)
				ifs.read(memblock, 1);
			if (ifs.eof())
				break;
			ifs.seekg(1, std::ios::cur);
		}
	}
	ifs.close();

	std::cout << "Reading data finished!\n" << std::endl;

	// Convert vc and fc into float and int array
	float* vertex_array = new float[vc.size()];
	for (std::size_t i=0; i<vc.size(); i++)
		vertex_array[i] = char_vector_to_float(vc[i]);

	int* face_array = new int[fc.size()];
	for(std::size_t i=0; i<fc.size(); i++)
		face_array[i] = char_vector_to_int(fc[i]);

	// Print arrays for debugging purpose
	std::cout << "Printing vertex_array..." << std::endl;
	for (std::size_t i=0; i<vc.size(); i++)
		std::cout << vertex_array[i] << " ";
	std::cout << std::endl;
	std::cout << "Printing face_array..." << std::endl;
	for (std::size_t i=0; i<fc.size(); i++)
		std::cout << face_array[i] << " ";
	std::cout << std::endl;

	// Pack the results into a struct.
	struct Mesh mesh;
	mesh.vertex_count = vc.size();	// XXX
	mesh.face_count = fc.size();	// XXX
	mesh.vertex_array = vertex_array;
	mesh.face_array = face_array;

	return mesh;
}

/**
   Convert .plum file directly into a VBO data array.
*/
GLfloat* plum_loader_vbo(const char* filename)
{
	struct Mesh mesh = plum_loader(filename);
	const int vbo_size = mesh.face_count * 3;
	GLfloat* vbo_list = new GLfloat[vbo_size];

	std::cout << "Vertex count: " << mesh.vertex_count << std::endl;
	std::cout << "Face count: " << mesh.face_count << std::endl;

	for (int i=0; i<mesh.face_count; i++) {
		vbo_list[i*3]   = mesh.vertex_array[mesh.face_array[i]*3];
		vbo_list[i*3+1] = mesh.vertex_array[mesh.face_array[i]*3+1];
		vbo_list[i*3+2] = mesh.vertex_array[mesh.face_array[i]*3+2];
	}

	// Print VBOList items
	std::cout << "Printing vbo_list[]..." << std::endl;
	for (int i=0; i<vbo_size; i++)
		std::cout << vbo_list[i] << " ";
	std::cout << std::endl;

	return vbo_list;
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
