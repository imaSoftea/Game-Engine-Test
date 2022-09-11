// Carter Thompson
// Work In Progress Game Engine
#include "Main.h"

//Window Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Main Program
int main() 
{
    //Initiantiating GLFW Window
    glfwInit();

    //Configuring Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creating a Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    //On Failure w/ Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Setting Viewport Size and Setting Callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex Floats 2-D
    int vertSize = 8;
    float triangleVert[] =
    {
         -0.5f, 0.5f,

          0.5f, 0.5f,

         -0.5f, -0.5f,

          0.5f, -0.5f
    };

    //Buffers
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int bufferOne;
    glGenBuffers(1, &bufferOne);
    glBindBuffer(GL_ARRAY_BUFFER, bufferOne);   
    glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float), triangleVert, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    

    //Shader Stuff
    ShaderSourceText shaderText = ReadShader("Shaders/default.shader");
    std::cout << "VERTEX" << std::endl;
    std::cout << shaderText.vertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << shaderText.fragSource << std::endl;
    unsigned int shader = CreateShader(shaderText.vertexSource,shaderText.fragSource);
    glUseProgram(shader);

    //Main Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //Drawing
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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

// Window Functions

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

