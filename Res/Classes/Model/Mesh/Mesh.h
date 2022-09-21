#ifndef MESH
#define MESH
#include <vector>
#include <iostream>

using namespace std;

class Mesh
{
	private:
		//Member Variables
		vector<float> verticeData;
		vector<float> textureMap;
		vector<unsigned int> indexOrder;

	public:
		//Getter Functions
		float* getVerticeData();
		float* getTextureMap();
		unsigned int* getIndexOrder();

		//Functions to get sizes...
		int vertSize();
		int texVertSize();
		int indexSize();

		//Constructor
		Mesh();
};

#endif 