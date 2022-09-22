#ifndef MODEL

#include "..\Texture\Texture.h"
#include "Mesh\Mesh.h"
#include "..\General\Transform.h"

class Model
{
	private: 
		Mesh mesh;
		Texture texture;
		unsigned int shader;
		Transform transform;
		int transformationUniform;

	public:
		//Getter Functions
		Mesh getMesh();
		Texture getTexture();
		Transform& getTransform();

		//Transformations

		//Render Object
		void renderModel();

		//Constructor
		Model(unsigned int shader);
};

#endif
