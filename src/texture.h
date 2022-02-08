#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
private:
    unsigned int m_id;
    unsigned int loadTexture(const char* imagePath);
public:
    Texture() {}
    Texture(const char* imagePath);
    unsigned int& id() { return m_id; }
};

#endif