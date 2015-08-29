#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Mesh plum_loader(const char* filename);
double* plum_loader_vbo(const char* filename);
double char_vector_to_float(std::vector<char> charvec);
int char_vector_to_int(std::vector<char> charvec);

struct Mesh {
	int vertex_count;
	int face_count;
	double* vertex_array;
	int* face_array;

	// Destructor
	~Mesh() {
		std::cout << "Destructing!" << std::endl;
		delete [] vertex_array;
		delete [] face_array;
	}
};

int main()
{
	plum_loader_vbo("examples/example.plum");
	return 0;
}

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

	std::cout << "The file opened successfully. Reading data from file to a container..." << std::endl;

	// create vector containers
	std::vector<std::vector<char> > vc;	// vertex container for all of the vertex data
	std::vector<std::vector<char> > fc;	// facial vertex container for all of the VBO data

	// start a loop to find all the vertex data & store it in vc
	char memblock[1];

	while(true) {
		std::vector<char> tempvec;	// Only used inside while loop, so declare here

		ifs.read(memblock, 1);

		if(memblock[0] == 'v') {		// Vertex line
			ifs.seekg(1, std::ios::cur);

			while (true) {
				ifs.read(memblock, 1);

				if (memblock[0] != 0x20 && memblock[0] != 0x0d) {
					std::cout << memblock[0];
					tempvec.push_back(memblock[0]);
				} else if (memblock[0] == 0x20) { // 0x20: Space
					vc.push_back(tempvec);
					tempvec.clear();
					std::cout << " ";
				} else {			  // 0x0d: newline
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
		} else {  				// Nothing to read, skip to the next line
			while (memblock[0] != 0x0d)
				ifs.read(memblock, 1);
			if (ifs.eof())
				break;
			ifs.seekg(1, std::ios::cur);
		}
	}
	ifs.close();

	std::cout << "Reading data finished!\n" << std::endl;

	// Convert vc and fc into double and int array
	double* vertex_array = new double[vc.size()];
	for (int i=0; i<vc.size(); i++)
		vertex_array[i] = char_vector_to_float(vc[i]);

	int* face_array = new int[fc.size()];
	for(int i=0; i<fc.size(); i++)
		face_array[i] = char_vector_to_int(fc[i]);

	// Print arrays for debugging purpose
	std::cout << "Printing vertex_array..." << std::endl;
	for (int i=0; i<vc.size(); i++)
		std::cout << vertex_array[i] << " ";
	std::cout << std::endl;
	std::cout << "Printing face_array..." << std::endl;
	for (int i=0; i<fc.size(); i++)
		std::cout << face_array[i] << " ";
	std::cout << std::endl;

	// Construct the struct data
	struct Mesh mesh;
	mesh.vertex_count = vc.size();	// XXX
	mesh.face_count = fc.size();	// XXX
	mesh.vertex_array = vertex_array;
	mesh.face_array = face_array;

	return mesh;
}

double* plum_loader_vbo(const char* filename)
{
	struct Mesh mesh = plum_loader(filename);
	const int vbo_size = mesh.face_count * 3;
	double* vbo_list = new double[vbo_size];

	for(int i=0; i<mesh.face_count; i++)
	{
		vbo_list[i*3]   = mesh.vertex_array[mesh.face_array[i]*3];
		vbo_list[i*3+1] = mesh.vertex_array[mesh.face_array[i]*3+1];
		vbo_list[i*3+2] = mesh.vertex_array[mesh.face_array[i]*3+2];
	}

	// Print VBOList items
	std::cout << "Printing VBOList[]..." << std::endl;
	for (int i=0; i<vbo_size; i++)
		std::cout << vbo_list[i] << " ";
	std::cout << std::endl;

	return vbo_list;
}

/**
   Convert vector<char> to float and return it.
*/
double char_vector_to_float(std::vector<char> charvec)
{
	// Method: "Let's love STL!"
	// First convert char vector into a string,
	// and then use string STL to convert it into a double.

	std::string str(charvec.begin(), charvec.end());
	return std::stod(str);
}

/**
   Convert vector<char> to int and return it.
*/
int char_vector_to_int(std::vector<char> charvec)
{
	std::string str(charvec.begin(), charvec.end());
	return std::stoi(str);
}
