#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include <vector>
#include <string>

#include "model.h"

class SceneRenderer {
private:
    std::vector<Model> models;
public:
    SceneRenderer() {}
};

#endif;