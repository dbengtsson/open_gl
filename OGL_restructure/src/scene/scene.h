#ifndef SCENE_H
#define SCENE_H

#include <scenerenderer.h>

class Scene {
private:
    SceneRenderer renderer;
public:
    draw();
};

void Scene::draw() {
    renderer.draw();
}
#endif