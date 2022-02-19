#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction;
    float movementSpeed = 50.0f;
    float fov;
    float aspectRatio;

    void updateCamera()
    {
        direction = glm::normalize(position - target);
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(worldUp, direction));
        glm::vec3 up = glm::normalize(glm::cross(direction, right));
        target = target;
    }
public:
    Camera() {};
    Camera(float fov, float aspectRatio) {
        this->fov = fov;
        this->aspectRatio = aspectRatio;
        updateCamera();
    }

    float getMovementSpeed() { return movementSpeed; }
    glm::vec3 getPosition() { return position; }
    glm::vec3 getDirection() { return -direction; }
    glm::vec3 getTarget() { return target; }
    glm::vec3 getUp() { return up; }

    void setPosition(glm::vec3 position) {
        this->position = position;
        updateCamera();
    }

    void setTarget(glm::vec3 target) {
        this->target = target;
        updateCamera();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), up);
    }

    glm::mat4 getProjectionMatrix() {
        return glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
    }
};

#endif