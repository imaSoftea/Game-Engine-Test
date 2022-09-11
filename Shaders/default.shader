// Shader File
// Added a comment system when file is read...



// All code for the vertex shader goes here

#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

// All code for the fragment shader goes here

#shader frag
#version 330 core

layout(location = 0) out vec4 color;

void main()
{

	color = vec4(1.0, 0.0, 0.0, 1.0);

}