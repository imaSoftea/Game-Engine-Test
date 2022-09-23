#include "BuildScene.h"

vector <Model> CreateScene()
{
    //Shader Stuff
    string location = "Shaders/default.shader";
    Shader cubeShader(location);
    glUseProgram(cubeShader.getProgram());

    unsigned int colorLocation = glGetUniformLocation(cubeShader.getProgram(), "aColor");
    if (colorLocation == -1)
    {
        std::cout << "Uniform Not Found: Color";
    }

    //Creating my cube models
    Model cubeOne(cubeShader.getProgram());
    cubeOne.getTransform().translatePos(-1.0f, 0.0f, -3.0f);
    Model cubeTwo(cubeShader.getProgram());
    cubeTwo.getTransform().translatePos(1.0f, 0.0f, -3.0f);

    // "Going 3-D"
    mat4 projection;
    projection = perspective(radians(45.0f), 1000.0f / 1000.0f, 0.1f, 100.0f);
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -5.0f));

    //Setting 3-D Uniforms
    int viewLoc = glGetUniformLocation(cubeShader.getProgram(), "aView");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    int projLoc = glGetUniformLocation(cubeShader.getProgram(), "aProjection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

    // Test Color Variables (TO BE REMOVED)
    Color testColor = { 1.0f , 1.0f , 1.0f , 1.0f };
    glUniform4f(colorLocation, testColor.red, testColor.green, testColor.blue, testColor.alpha);

    vector <Model> models =
    {
        cubeOne, cubeTwo
    };
    return models;
	
}

void RenderScene(vector <Model>& models)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    int size = (int)models.size();
    for (int i = 0; i < size; i++)
    {
        models[i].renderModel();
        models[i].getTransform().rotatePos(1.0f, 1.0f, 1.0f, 0.0f);
    };
}

