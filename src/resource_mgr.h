#ifndef RESOURCE_MGR_H
#define RESOURCE_MGR_H

#include <map>
#include <string>
#include <iostream>

#include "texture.h"

class ResourceMgr {
private:
    std::map<std::string, Texture> textures;
public:
    ResourceMgr() {}
    // const Texture& getTexture(const char* id) { return textures.at(id); }
    unsigned int loadTexture(const char* filePath) {
        if (textures.count(filePath)) {
            return textures[filePath].id();
        } else {
            Texture t(filePath);
            textures.insert({ filePath, t });
            return t.id();
        }
    }
};

#endif