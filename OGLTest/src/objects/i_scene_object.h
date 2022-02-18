#ifndef I_SCENE_OBJECT_H
#define I_SCENE_OBJECT_H

// #include "camera.h"
#include <glm/glm.hpp>

class ISceneObject {
protected:
    glm::vec3 _position = glm::vec3(0.0f);
    float _scale = 1.0f;
    // virtual ~ISceneObject();
public:
    // ISceneObject(const Camera& cam);
    virtual void update(unsigned int deltaTime) = 0;
    // virtual void render() = 0;
    virtual void render() = 0;

    const glm::vec3& position() { return _position; };
    void position(const glm::vec3& position) { _position = position; };

    float scale() { return _scale; }
    void scale(float scale) { _scale = scale; }
};

// ISceneObject::ISceneObject(const Camera& cam) {
//     _viewMatrix = cam.view();
//     _projectionMatrix = cam.projection();
// }

#endif