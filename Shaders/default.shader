// Shader File
// Added a comment system when file is read...



// All code for the vertex shader goes here
#shader vertex
#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 aView;
uniform mat4 aProjection;
uniform mat4 aModel;

void main()
{
	gl_Position = aProjection * aView * aModel * vec4(aPosition.xyz, 1.0);
	TexCoord = aTexCoord;
}



// All code for the fragment shader goes here
#shader fragment
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec4 aColor;
uniform sampler2D aTexture;

void main()
{
	FragColor = texture(aTexture, TexCoord) * (aColor);
}	