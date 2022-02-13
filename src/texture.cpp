
#include "texture.h"
#include <glad/glad.h>
#include <iostream>

#include "image.h"

Texture::Texture(const char* imagePath) {
    _id = loadTexture(imagePath);
}

unsigned int Texture::loadTexture(const char* imagePath) {
    unsigned int texture;
    // Generate texture and retrieve id
    glGenTextures(1, &texture);
    // Set the currently bound texture to work with.
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set texture parameters on currently bound texture.
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Image textureImage(imagePath, true);
    if (textureImage.getData())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.getWidth(), textureImage.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Failed to load texture:");
    }
    
    std::cout << texture << std::endl;
    return texture;
}