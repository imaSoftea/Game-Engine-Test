#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


//Constructor
class Transform
{

	private:
		mat4 modelPos;

	public:
		//Getters
		mat4& getModelPos();

		//Transformation Commands
		void rotatePos(float deg, float x, float y, float z);
		void translatePos(float x, float y, float z);

		//Constructor
		Transform();
};

#endif