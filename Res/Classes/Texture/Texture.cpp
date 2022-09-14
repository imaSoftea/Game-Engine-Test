#include "Texture.h"

// Binds the Texture Class
void Texture::Bind()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}

// Sets the Parameters of the Texture (to be customizable later)
void  Texture::SetParams()
{
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// Loads the texture from a file
void  Texture::LoadTexture(unsigned int shader)
{
    // Loading Textures
    unsigned char* data = stbi_load(fileLocation.c_str(), &texWidth, &texHeight, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {   
        //Error Handling
        std::cout << "Texture not Loaded" << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);
    int texLocation = glGetUniformLocation(shader, "aTexture");
    if (texLocation == -1)
    {
        "Texture Uniform Not Found";
    }
}
