// #ifndef TEXTURE_H
// #define TEXTURE_H

// #include <glad/glad.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #include <string>

// class Texture {
// private:
//     uint32_t m_textureId;
//     std::string m_type;
// public:
//     ~Texture() {}

//     Texture() {}
//     Texture(const char* filePath) {
//         int w, h, channels;
//         stbi_set_flip_vertically_on_load(true);
//         unsigned char* pixels = stbi_load(filePath, &w, &h, &channels, 0);

//         uint32_t texture;
//         // Generate texture and retrieve id
//         glGenTextures(1, &texture);
//         // Set the currently bound texture to work with.
//         glBindTexture(GL_TEXTURE_2D, texture);
//         // Set texture parameters on currently bound texture.
//         // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//         if (pixels) {
//             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
//             glGenerateMipmap(GL_TEXTURE_2D);
//             m_textureId = texture;
//         }
//         else {
//             throw std::runtime_error("Failed to load texture.");
//         }
//         stbi_image_free(pixels);
//     }
    
//     uint32_t getId() { return m_textureId; }
//     std::string getType() { return m_type; }
// };

// #endif