// Carter Thompson
// Work In Progress Game Engine

//In Progress - Abstraction 

#include "Main.h"
using namespace glm;

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
    GLFWwindow* window = glfwCreateWindow(1080, 1080, "Game Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    
    //On Failure w/ Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Setting Viewport Size and Setting Callback
    glViewport(0, 0, 1080, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex Floats 2-D
    int vertSize = 12;
    int texVertSize = 8;
    float triangleVert[] =
    {
          -1.0f, -1.0, 1.0f,    

          -1.0f,  1.0f,  1.0f,   

           1.0f,  -1.0f,  1.0f,   

           1.0f,  1.0f,  1.0f

    };
    float triangleTexVert[] =
    {
        0.0f, 0.0f,

        0.0f, 1.0f,

        1.0f, 0.0f,

        1.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    unsigned int bufferTwo;
    glGenBuffers(1, &bufferTwo);
    glBindBuffer(GL_ARRAY_BUFFER, bufferTwo);
    glBufferData(GL_ARRAY_BUFFER, texVertSize * sizeof(float), triangleTexVert, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    

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

    // Create a Texture
    Texture woodTexture;
    woodTexture.fileLocation = "Res/Textures/Wood.jpg";
    woodTexture.Bind();
    woodTexture.SetParams();
    woodTexture.LoadTexture(shader);

    // Creating & Testing Transformations
 
    // "Going 3-D"
    mat4 model = mat4(1.0f);
    model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
    mat4 projection;
    projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -3.0f));
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
    bool isGoingUp = true;

    //Main Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //Drawing
        glBindTexture(GL_TEXTURE_2D, woodTexture.texture);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode for testing

        //Test Rotations
        model = rotate(model, radians(5.0f), vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
        glUniform4f(colorLocation, testColor.red, testColor.green, testColor.blue, testColor.alpha);
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