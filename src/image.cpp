#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Image::~Image() {
    std::cout << "Unloading image from memory: " << filePath;
    stbi_image_free(data);
    std::cout << "... DONE" << std::endl;
}

Image::Image(const char* filePath) {
    load(filePath);
}

Image::Image(const char* filePath, bool flipVertically) {
    stbi_set_flip_vertically_on_load(flipVertically);
    load(filePath);
}

void Image::load(const char* filePath) {
    std::cout << "Loading image from disk: " << filePath;
    this->data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    this->filePath = filePath;
    std::cout << "... DONE" << std::endl;
}