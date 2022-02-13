#ifndef I_SCENE_OBJECT_H
#define I_SCENE_OBJECT_H

// #include "camera.h"
#include <glm/glm.hpp>

class ISceneObject {
protected:
    glm::vec3 _position;
    // virtual ~ISceneObject();
public:
    // ISceneObject(const Camera& cam);
    virtual void update(unsigned int deltaTime) = 0;
    // virtual void render() = 0;
    virtual void render() = 0;

    const glm::vec3& position() { return _position; };
    void position(const glm::vec3& position) { _position = position; };
};

// ISceneObject::ISceneObject(const Camera& cam) {
//     _viewMatrix = cam.view();
//     _projectionMatrix = cam.projection();
// }

#endif