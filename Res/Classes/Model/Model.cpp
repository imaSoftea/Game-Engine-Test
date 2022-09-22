#include "Model.h"

//Getter Functions
Mesh Model::getMesh()
{
	return mesh;
}
Texture Model::getTexture()
{
	return texture;
}
Transform& Model::getTransform()
{
    return transform;
}

void Model::renderModel()
{
    //Buffers
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int bufferOne; //Position
    glGenBuffers(1, &bufferOne);
    glBindBuffer(GL_ARRAY_BUFFER, bufferOne);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertSize() * sizeof(float), mesh.getVerticeData(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    unsigned int bufferTwo;
    glGenBuffers(1, &bufferTwo); //Texture
    glBindBuffer(GL_ARRAY_BUFFER, bufferTwo);
    glBufferData(GL_ARRAY_BUFFER, mesh.texVertSize() * sizeof(float), mesh.getTextureMap(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer); //Index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indexSize(), mesh.getIndexOrder(), GL_STATIC_DRAW);

    //Shader Loading
    glBindTexture(GL_TEXTURE_2D, texture.texture); //Im sorry this naming is horrible... will change

    //Set Unforms
    glUniformMatrix4fv(transformationUniform, 1, GL_FALSE, value_ptr(getTransform().getModelPos()));

    //Drawing
    glDrawElements(GL_TRIANGLES, mesh.indexSize(), GL_UNSIGNED_INT, NULL); 
}

Model::Model(unsigned int aShader)
{
    //Assigning Texture
    Texture woodTexture;
    woodTexture.fileLocation = "Res/Textures/Wood.jpg";
    woodTexture.Bind();
    woodTexture.SetParams();
    texture = woodTexture;
    texture.LoadTexture(shader);
    shader = aShader;

    //Setting up Unform Stuff
    transformationUniform = glGetUniformLocation(shader, "aModel");
}