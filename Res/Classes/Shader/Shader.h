#ifndef SHADER
#define SHADER

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

class Shader
{
	private:
		ShaderSourceText shaderSourceText;
		unsigned int program;

	public:

		//Getter
		unsigned int getProgram();

		//Compiling & Reading
		unsigned int CompileShader(unsigned int type, const std::string& source);
		void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		void ReadShader(const std::string& filePath);

		Shader(std::string& filePath);
};


#endif