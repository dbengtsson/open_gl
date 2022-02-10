#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "i_scene_object.h"

class Camera : public ISceneObject {
private:
    glm::vec3 _cameraPosition = glm::vec3(6.0f, 2.0f, 4.0f);
    glm::vec3 _cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _cameraDirection = glm::normalize(_cameraPosition - _cameraTarget);
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _cameraRight = glm::normalize(glm::cross(_up, _cameraPosition));
    glm::vec3 _cameraUp = glm::cross(_cameraDirection, cameraRight);

public:
    Camera();
    void translate(glm::vec3 
};



#endif