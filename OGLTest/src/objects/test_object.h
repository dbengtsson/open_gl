#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "i_scene_object.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../shader.h"
#include "../texture.h"
#include "../resource_mgr.h"

const char* TEXTURE0_FILEPATH = "res/karingo.tga";
const char* TEXTURE1_FILEPATH = "res/hunt.tga";

// const float vertices[180] = {
//         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//     };

const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

class TestObject : public ISceneObject {
private:
    float rotation = 30.0f;
    // TODO: Do not have these per object basis.
    // Pass in scene and have a resource manager there
    unsigned int _loadedTextures[2];
    Shader* _shader;
public:
    ~TestObject();
    TestObject(ResourceMgr& resourceMgr, Shader* shader);
    void update(unsigned int deltaTime) override;
    void render() override;
    void position(const glm::vec3& position) { _position = position; }
};

TestObject::~TestObject() {}

TestObject::TestObject(ResourceMgr& resourceMgr, Shader* shader) {
    _shader = shader;
    _position = glm::vec3(0.0f);
    // Load textures
    _loadedTextures[0] = resourceMgr.loadTexture(TEXTURE0_FILEPATH);
    _loadedTextures[1] = resourceMgr.loadTexture(TEXTURE1_FILEPATH);
}

void TestObject::update(unsigned int deltaTime) {};

void TestObject::render() {
    // Bind textures
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _loadedTextures[0]);

    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _loadedTextures[1]);

    // Set active shader and assign textures
    _shader->setValue("texture1", 0);
    _shader->setValue("texture2", 1);
    
    float blend = 0.5f * (1.0f + sin(2 * M_PI * 0.1f * glfwGetTime()));
    _shader->setValue("blending", blend);

    // Draw a single box
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = glm::scale(model, glm::vec3(_scale));
    // model = glm::rotate(model, glm::radians(-rotation), glm::vec3(1.0f, 0.0f, 0.0f));
    // float rotateY = 360.0f * (1.0f + sin(2.0f * M_PI * 0.2f * glfwGetTime()));
    // model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
    _shader->setModelMatrix(model);

    // Draw all triangles
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Unbind texture for next object
    glBindTexture(GL_TEXTURE_2D, 0);

    // _shader->use();
    // _shader->setValue("texture1", 0);
    // _shader->setValue("texture2", 1);

    
    // // float rotation = sin(time * 2) * -45.0f;
    // // cubeRotation[i]
    // float scale = 1.0f + 0.25f + sin(2 * M_PI * 0.25f * time) * 0.25f;
    
    // // glm::mat4 transform = glm::mat4(1.0f);
    // // transform = glm::translate(transform, glm::vec3(0.2f, 0.2f, 0.0f));
    // // transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    // // transform = glm::scale(transform, glm::vec3(scale));
    
    // // m_shader->setValue("transform", transform);

    // float blend = 0.5f * (1.0f + sin(2 * M_PI * 0.5f * time));
    // _shader->setValue("blending", blend);
}

#endif