// Carter Thompson
// Work In Progress Game Engine

#include "Main.h"

//Window Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Color Class (TO BE MOVED)
class Color
{
    public:
        float red;
        float green;
        float blue;
        float alpha;

        Color(float aRed, float aGreen, float aBlue, float aAlpha)
        {
            red = aRed;
            green = aGreen;
            blue = aBlue;
            alpha = aAlpha;
        }
};


void ColorWheel(Color &inputColor, bool &isGoingUp);

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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
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
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex Floats 2-D
    int vertSize = 12;
    int texVertSize = 8;
    float triangleVert[] =
    {
          -0.5f, -0.5f, 0.0f,    

          -0.5f,  0.5f,  0.0f,   

           0.5f,  -0.5f,  0.0f,   

           0.5,  0.5f,  0.0f
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

    int colorLocation = glGetUniformLocation(shader, "aColor");
    if (colorLocation == -1)
    {
         std::cout << "Uniform Not Found";
    }

    //Texturing Settings

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texWidth, texHeight, nrChannels;
    unsigned char* data = stbi_load("Res/Textures/Wood.jpg", &texWidth, &texHeight, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture not Loaded" << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);
    int texLocation = glGetUniformLocation(shader, "aTexture");
    if (texLocation == -1)
    {
        "Texture Uniform Not Found";
    }
    

    
   

    // Test Color Variables (TO BE REMOVED)
    Color testColor = { 0.3f , 0.3f , 1.0f , 1.0f };
    bool isGoingUp = true;

    //Main Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //Drawing
        glBindTexture(GL_TEXTURE_2D, texture);
        ColorWheel(testColor, isGoingUp); //ColorWheel Mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode
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


//Color Function (TO BE REMOVED)

void ColorWheel(Color &inputColor, bool &isGoingUp)
{
    float inc;

    if (isGoingUp)
    {
        inc = 0.02f;
    }
    else
    {
        inc = -0.02f;
    }

    if (inputColor.blue > 1.0f)
    {
        isGoingUp = false;
    }
    else if (inputColor.blue < 0.0f)
    {
        isGoingUp = true;
    }

    inputColor.blue += inc;
    inputColor.red -= inc;
}
