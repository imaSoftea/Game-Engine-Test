#include "Window.h"

//Adjusting viewport on resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//Processes inputs
void processInput(GLFWwindow* window)
{
    //This exits the program on hitting the "Escape" key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* CreateWindow()
{
    //Initiantiating GLFW Window
    glfwInit();

    //Configuring Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creating a Window
    GLFWwindow* window = glfwCreateWindow(1080, 1080, "Game Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        abort();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    //On Failure w/ Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        abort();
    }

    //Setting Viewport Size and Setting Callback
    glViewport(0, 0, 1080, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

