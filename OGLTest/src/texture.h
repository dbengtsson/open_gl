#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
private:
    unsigned int _id;
    unsigned int loadTexture(const char* imagePath);
public:
    Texture() {}
    Texture(const char* imagePath);
    unsigned int id() { return _id; }
};

#endif