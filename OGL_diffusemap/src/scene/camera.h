#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    // glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right, direction;
    float movementSpeed = 5.0f;
    float fov, aspectRatio;
    float yaw, pitch, roll;
public:
    Camera() {};
    Camera(float fov, float aspectRatio) {
        this->fov = fov;
        this->aspectRatio = aspectRatio;
        this->yaw = -90;
        updateCamera();
    }

    float getMovementSpeed() { return movementSpeed; }
    glm::vec3 getPosition() { return position; }
    glm::vec3 getDirection() { return -direction; }
    glm::vec3 getUp() { return up; }
    float getYaw() { return yaw; }
    float getPitch() { return pitch; }

    void setYaw(float yaw) { this->yaw = yaw; }
    void setPitch(float pitch) { this->pitch = pitch; }

    void setPosition(glm::vec3 position) {
        this->position = position;
        updateCamera();
    }

    void setDirection(glm::vec3 direction) {
        this->direction = direction;
        updateCamera();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + direction, up);
    }

    glm::mat4 getProjectionMatrix() {
        return glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
    }

    void updateCamera()
    {
        direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        direction.y = glm::sin(glm::radians(pitch));
        direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        direction = normalize(direction);
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::normalize(glm::cross(worldUp, direction));
        up = glm::normalize(glm::cross(direction, right));
    }
};

#endif