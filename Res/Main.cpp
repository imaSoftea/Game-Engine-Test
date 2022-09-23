// Carter Thompson
// Work In Progress Game/Render Engine

//In Progress - Abstraction 

#include "Main.h"

//Main Program
int main() 
{   
    GLFWwindow* window = CreateWindow();
    vector <Model> models = CreateScene();

    //Main Loop
    while (!glfwWindowShouldClose(window))
    {
        //Buffering & Events
        glfwSwapBuffers(window);
        glfwPollEvents();

        //Render Scene
        RenderScene(models);

        //Input Processing
        processInput(window);
    }
    glfwTerminate();

    return 0;
}