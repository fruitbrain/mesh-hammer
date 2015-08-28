#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

std::vector<double> DrawMesh();
double strToFloat(std::vector<char> charvec);
int strToInt(std::vector<char> charvec);

int main()
{
	DrawMesh();
	//std::cout << (int)'1' << std::endl;
	return 0;
}

std::vector<double> DrawMesh()
{
	// open an input stream for the file for vertex data collection
	std::cout << "opening an input stream for the file" << std::endl;
	std::ifstream ifs("example.plum", std::ios::in|std::ios::binary);
	
	if(!ifs.is_open())
		std::cerr << "ERROR : The file did not open." << std::endl;
	
	std::cout << "The file opened successfully. Reading data from file to a container..." << std::endl;
	
	// create a vector container for all of the vertex data
	std::vector<std::vector<char> > vc;	// vertex container
	
	// start a loop to find all the vertex data & store it in vc
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
					vc.push_back(tempvec);
					tempvec.clear();
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
	
	std::cout << "Reading data finished!\n" << std::endl;
	ifs.close();
	
	// change std::vector<std::vector<char> > into a std::vector<double>
	std::vector<double> vertexList;
	
	for(int i=0; i<vc.size(); i++)
		vertexList.push_back(strToFloat(vc[i]));
		
	for(int i=0; i<vertexList.size(); i++)
		std::cout << vertexList[i] << std::endl;
	
	// open an input stream (again) for the (same) file for face data collection
	std::cout << "opening an input stream for the file" << std::endl;
	std::ifstream ifs2("example.plum", std::ios::in|std::ios::binary);
	
	if(!ifs2.is_open())
		std::cerr << "ERROR : The file did not open." << std::endl;
	
	std::cout << "The file opened successfully. Reading data from file to a vector..." << std::endl;
	
	// creating a facial vertex container for all of the VBO data
	std::vector<std::vector<char> > fc;	// face container
	tempvec.clear();
	
	while(true)
	{
		ifs2.read(memblock, 1);
		
		if(memblock[0] == 'f')
		{	
			ifs2.seekg(1, std::ios::cur);
			
			while(true)
			{
				ifs2.read(memblock, 1);
				
				if(memblock[0] != 0x20 && memblock[0] != 0x0d)
				{
					std::cout << memblock[0];
					tempvec.push_back(memblock[0]);
				}
				else if(memblock[0] == 0x20)
				{
					fc.push_back(tempvec);
					tempvec.clear();
					std::cout << " ";
				}
				else
				{
					fc.push_back(tempvec);
					tempvec.clear();
					ifs2.seekg(1, std::ios::cur);
					std::cout << std::endl;
					break;
				}
			}
		}
		
		else
		{
			while(memblock[0] != 0x0d)
				ifs2.read(memblock, 1);
			if(ifs2.eof())
				break;
			ifs2.seekg(1, std::ios::cur);
		}
	}
	
	std::cout << "Reading data finished!\n" << std::endl;
	ifs.close();
	
	// change std::vector<std::vector<char> > into a std::vector<int>
	std::vector<int> faceList;
	
	for(int i=0; i<vc.size(); i++)
		faceList.push_back(strToInt(fc[i]));
		
	// finally, make the vector data that is fed into the VBO
	std::vector<double> VBOList;
	
	for(int i=0; i<faceList.size(); i++)
	{
		//vertexList[faceList[i]];
	}
	
	return vertexList;
}

double strToFloat(std::vector<char> charvec)
{
	int size = charvec.size();
	double result = 0.0;
	
	if(charvec[0] == '-')
	{
		std::cout << "Hey its minus" << std::endl;
		for(int i=3; i<size; i++)
			result += ((int)charvec[0]-48)*pow(10, -(i-2));
		return (-1.0)*result;
	}
	else
	{
		std::cout << "Hey its plus" << std::endl;
		for(int i=2; i<size; i++)
			result += ((int)charvec[0]-48)*pow(10, -(i-1));
		return result;
	}
}

int strToInt(std::vector<char> charvec)
{
	int size = charvec.size();
	int result = 0;
	
	for(int i=0; i<size; i++)
		result += ((int)charvec[size-1-i]-48)*pow(10, i);
		
	return result;
}
