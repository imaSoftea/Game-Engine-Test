#ifndef SHADER_CREATE_FUNCTIONS
#define SHADER_CREATE_FUNCTIONS

#include <GLAD/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  

struct ShaderSourceText
{
    std::string vertexSource;
    std::string fragSource;
};

unsigned int CompileShader(unsigned int type, const std::string& source);
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
ShaderSourceText ReadShader(const std::string& filePath);

#endif