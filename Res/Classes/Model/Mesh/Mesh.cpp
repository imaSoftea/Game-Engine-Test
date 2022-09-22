#include "Mesh.h"

//Getter Definitions
float* Mesh::getVerticeData()
{
	return &verticeData[0];
}

float* Mesh::getTextureMap()
{
	return &textureMap[0];
}

unsigned int* Mesh::getIndexOrder()
{
	return &indexOrder[0];
}

//Data Size Functions
int Mesh::vertSize()
{
    return (int)verticeData.size();
}
int Mesh::texVertSize()
{
    return (int)textureMap.size();
}
int Mesh::indexSize()
{
    return (int)indexOrder.size();
}


//Default Constructor - Makes a cube...
Mesh::Mesh()
{
    vector <float> cubeVert =
    {
          -1.0f, -1.0, 1.0f,    //BL Front 0

          -1.0f,  1.0f,  1.0f,   //TL Front 1

           1.0f,  -1.0f,  1.0f,   // BR Front 2

           1.0f,  1.0f,  1.0f,    // TR Front 3


          -1.0f, -1.0, -1.0f,   // BL Back 4

          -1.0f,  1.0f,  -1.0f,   // TL Back 5

           1.0f,  -1.0f,  -1.0f,  // BR Back 6

           1.0f,  1.0f,  -1.0f   // TR Back 7

    };
    vector <float> cubeTexVert = //A bit off rn
    {
        0.0f, 0.0f,  //front
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,  //Back
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f

    };

   vector <unsigned int> cubeIndices =
    {
        0, 1, 2,  //front
        1, 2, 3,

        4, 5, 6,  //back
        5, 6, 7,

        2, 3, 7,  //right
        2, 7, 6,

        0, 1, 5,  //left
        0, 5, 4,

        0, 2, 6,  //bottom
        0, 6, 4,

        1, 3, 7,  //top
        1, 7, 5
    };

    verticeData = cubeVert;
    textureMap = cubeTexVert;
    indexOrder = cubeIndices;

}