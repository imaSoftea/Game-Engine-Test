#ifndef BUILD_SCENE
#define BUILD_SCENE

#include <vector>
#include "..\Classes\Model\Model.h"
#include "..\Classes\Shader\Shader.h"
#include "..\Classes\Texture\Texture.h"
#include "..\Classes\General\Color.cpp"

//Rendering out the Scene
vector <Model> CreateScene();
void RenderScene(vector <Model>& models);

#endif
