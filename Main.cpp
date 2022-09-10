#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



//Declaring Functions (probably removed later)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& framentShader);
static unsigned int CompileShader(unsigned int type, const std::string& source);

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
    int vertSize = 20;
    float triangleVert[] =
    {
         -0.5f, -0.5f,
         -0.3f, -0.3f,

          0.5f, 0.5f,
          0.3f, 0.3f,

          0.5f, -0.5f,
          0.3f, -0.3f,

          -0.5f, 0.5f,
          -0.3f, 0.3f,

         -0.5f, -0.5f,
         -0.3f, -0.3f
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
    const std::string vertexShader =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position; \n"
        "}\n";

    //Shader Stuff
    const std::string fragShader =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1, 1, 1, 1); \n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader,fragShader);
    glUseProgram(shader);

    //Main Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
            
        //Drawing
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);

        //Buffering & Events
        glfwSwapBuffers(window);
        glfwPollEvents();

        //Input Processing
        processInput(window);
    }

    glfwTerminate();
    return 0;
}

/*
    Area for Functions
    (probably to be moved later)
*/

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

//Creating Shaders
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader( GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int compileResult;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shaders..." << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

