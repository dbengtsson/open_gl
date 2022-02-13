#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "i_scene_object.h"

class Camera {
private:
    glm::vec3 _position;
    glm::vec3 _lookAt;
    glm::vec3 _direction;
    glm::vec3 _up;
    glm::mat4 _view;
    glm::mat4 _projection;

    float _fov;
    float _aspectRatio;

    void createViewMatrix() {
        glm::mat4 view = glm::mat4(1.0f);
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
        // Non free-look camera
        view = glm::lookAt(position(), lookAt(), up());
        _view = view;
        // view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
    }

    void createProjectionMatrix() {
        _projection = glm::perspective(_fov, _aspectRatio, 0.1f, 1000.0f);
    }
public:
    Camera(float fov, float aspectRatio);
    // void update(unsigned int deltaTime);
    // void render();

    // Getters
    const glm::vec3& position() { return _position; };
    const glm::vec3& lookAt() { return _lookAt; }
    const glm::vec3& direction() { return _direction; }
    const glm::vec3& up() { return _up; }
    const glm::mat4& view() { return _view; }
    const glm::mat4& projection() { return _projection; }
    // Setters
    void position(const glm::vec3& position) { _position = position; createViewMatrix(); }
    void lookAt(const glm::vec3& lookAt) { _lookAt = lookAt; createViewMatrix(); }
    void direction(const glm::vec3& direction) { _direction = direction; createViewMatrix(); };
    void up(const glm::vec3& up) { _up = up; createViewMatrix(); }
    void fov(float fov) { _fov = fov; createProjectionMatrix(); }
    void aspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; createProjectionMatrix(); }
};

Camera::Camera(float fov, float aspectRatio) {
    _position = glm::vec3(0.0f, 0.0f, 4.0f);
    _lookAt = glm::vec3(0.0f);
    _direction = glm::normalize(position() - lookAt());
    glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _position));
    _up = glm::cross(_direction, cameraRight);
    _fov = fov;
    _aspectRatio = aspectRatio;

    createViewMatrix();
    createProjectionMatrix();
}

// void Camera::update(unsigned int deltaTime) {
// }

// void Camera::render() {
//     // // View Matrix
//     // glm::mat4 view = glm::mat4(1.0f);
//     // // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
//     // // Non free-look camera
//     // // view = glm::lookAt(cameraPosition, cameralookAt, cameraUp);
//     // view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
//     // _shader->setViewMatrix(view);

//     // // Projection Matrix
//     // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 10000.0f);
//     // _shader->setProjectionMatrix(projection);
// };

#endif