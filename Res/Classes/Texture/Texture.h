#ifndef TEXTURE
#define TEXTURE

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

class Texture
{
    public:

        // Variables
        unsigned int texture;
        int texWidth, texHeight, nrChannels;
        unsigned char* data;
        std::string fileLocation;
        int texLocation;

        void Bind();
        void SetParams();
        void LoadTexture(unsigned int shader);
};

#endif