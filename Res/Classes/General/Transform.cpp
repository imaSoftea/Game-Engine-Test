#include "Transform.h"
#include <iostream>

//Getter Functions
mat4& Transform::getModelPos()
{
	return modelPos;
}

//Transformation Commands
void Transform::rotatePos(float deg, float x, float y, float z)
{
	modelPos = rotate(modelPos, radians(deg), vec3(x, y, z));
}

void Transform::translatePos(float x, float y, float z)
{
	modelPos = translate(modelPos, vec3(x, y, z));
}

Transform::Transform()
{
	modelPos = mat4(1.0f);
}
