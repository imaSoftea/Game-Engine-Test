#include "ShaderCreate.h"

//Compiles the Shader
unsigned int CompileShader(unsigned int type, const std::string& source)
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

//Creating Shaders
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderSourceText ReadShader(const std::string& filePath)
{
    //Get the stream
    std::ifstream stream(filePath);


    //More Varaibles
    std::string line;
    std::stringstream shaderText[2];

    //Shader Type
    enum class ShaderType
    {
        NONE = -1, VERT = 0, FRAG = 1
    };

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        //Allows for commenting and ignores "//" lines
        if (((line.find("//")) != std::string::npos) == false)
        {
            //Checking for declaration of shader type
            if (line.find("#shader") != std::string::npos)
            {
                // Checks for if its a fragment or vertex shader
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERT;
                }
                else if (line.find("frag") != std::string::npos)
                {
                    type = ShaderType::FRAG;
                }
            }
            //Pushing to Strings
            else
            {
                if (type == ShaderType::VERT)
                {
                    shaderText[0] << line << '\n';
                }

                else if (type == ShaderType::FRAG)
                {

                    shaderText[1] << line << '\n';
                }

            }
        }
    }
    ShaderSourceText shaderTextOut;
    shaderTextOut.vertexSource = shaderText[0].str();
    shaderTextOut.fragSource = shaderText[1].str();

    return shaderTextOut;
}



