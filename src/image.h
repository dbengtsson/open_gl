#ifndef IMAGE_H
#define IMAGE_H

class Image {
private:
    const char* filePath;
    int width, height, nrChannels;
    unsigned char *data;

    void load(const char* filePath);
public:
    ~Image();
    Image(const char* filePath);
    Image(const char* filePath, bool flipY);
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getNrChannels() { return nrChannels; }
    unsigned char* getData() { return data; }
};

#endif