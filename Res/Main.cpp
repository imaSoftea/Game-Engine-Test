// Carter Thompson
// Work In Progress Game Engine

//In Progress - Abstraction 

#include "Main.h"

using namespace glm;

//Main Program
int main() 
{   

    GLFWwindow* window = CreateWindow();

    //Shader Stuff
    ShaderSourceText shaderText = ReadShader("Shaders/default.shader");
    std::cout << "VERTEX" << std::endl;
    std::cout << shaderText.vertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << shaderText.fragSource << std::endl;

    unsigned int shader = CreateShader(shaderText.vertexSource,shaderText.fragSource);
    glUseProgram(shader);

    unsigned int colorLocation = glGetUniformLocation(shader, "aColor");
    if (colorLocation == -1)
    {
         std::cout << "Uniform Not Found: Color";
    }

    // "Going 3-D"
    mat4 model = mat4(1.0f);
    model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    mat4 projection;
    projection = perspective(radians(45.0f), 1000.0f / 1000.0f, 0.1f, 100.0f);
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -5.0f));
    model = scale(model, vec3(0.5f, 0.5f, 0.5f));

    //Setting 3-D Uniforms
    int modelLoc = glGetUniformLocation(shader, "aModel");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
    int viewLoc = glGetUniformLocation(shader, "aView");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    int projLoc = glGetUniformLocation(shader, "aProjection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

    // Test Color Variables (TO BE REMOVED)
    Color testColor = { 1.0f , 1.0f , 1.0f , 1.0f };

    //Creating my cube model
    Model cubeOne(shader);

    //Main Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        cubeOne.renderModel();

        //Test Rotations
        model = rotate(model, radians(0.4f), vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
        glUniform4f(colorLocation, testColor.red, testColor.green, testColor.blue, testColor.alpha);;

        //Buffering & Events
        glfwSwapBuffers(window);
        glfwPollEvents();

        //Input Processing
        processInput(window);
    }

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}