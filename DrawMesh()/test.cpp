#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

std::vector<double> DrawMesh();
double strToFloat(std::vector<char> charvec);

int main()
{
	DrawMesh();

	return 0;
}

std::vector<double> DrawMesh()
{
	std::cout << "Hello OpenGL" << std::endl;

	// opening an input stream for the file

	std::ifstream ifs("example.plum", std::ios::in|std::ios::binary);

	if(!ifs.is_open())
	{
		std::cerr << "ERROR : The file did not open." << std::endl;
	}

	std::cout << "The file opened successfully. Reading data from file to a vector..." << std::endl;

	// creating a vector container for all of the vertex data

	std::vector<std::vector<char> > vc;

	// start a loop to find all the vertex data & store it in a vector

	char memblock[] = {' '};
	std::vector<char> tempvec;

	while(true)
	{
		ifs.read(memblock, 1);
		if(memblock[0] == 'v')
		{
			ifs.seekg(1, std::ios::cur);

			while(true)
			{
				ifs.read(memblock, 1);
				if(memblock[0] != 0x20 && memblock[0] != 0x0d)
				{
					std::cout << memblock[0];
					tempvec.push_back(memblock[0]);
				}
				else if(memblock[0] == 0x20)
				{
					vc.push_back(tempvec);
					tempvec.clear();
					std::cout << " ";
				}
				else
				{
					ifs.seekg(1, std::ios::cur);
					std::cout << std::endl;
					break;
				}
			}
		}

		else
		{
			while(memblock[0] != 0x0d)
				ifs.read(memblock, 1);
			if(ifs.eof())
				break;
			ifs.seekg(1, std::ios::cur);
		}
	}

	ifs.close();
	std::cout << "Reading data finished!" << std::endl;

	// change std::vector<std::vector<char> > into a std::vector<double> - char to double transformation

	std::vector<double> vertexList;

	for(int i=0; i<vc.size(); i++)
	{
		vertexList.push_back(strToFloat(vc[i]));
	}

	return vertexList;
}

double strToFloat(std::vector<char> charvec)
{
	int size = charvec.size();
	double result = 0.0;

	if(charvec[0] == '-')
	{
		for(int i=3; i<size; i++)
			result += ((int)charvec[0]-48)*pow(10, -(i-3));
		return -result;
	}
	else
	{
		for(int i=2; i<size; i++)
			result += ((int)charvec[0]-48)*pow(10, -(i-2));
		return result;
	}
}
