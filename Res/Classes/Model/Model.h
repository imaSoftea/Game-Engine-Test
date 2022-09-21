#ifndef MODEL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\Texture\Texture.h"
#include "Mesh\Mesh.h"

class Model
{
	private: 
		Mesh mesh;
		Texture texture;
		unsigned int shader;

	public:
		Mesh getMesh();
		Texture getTexture();

		void renderModel();

		//Constructor
		Model(unsigned int shader);
};

#endif
