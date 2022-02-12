#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "i_scene_object.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../shader.h"
#include "../texture.h"

const char* VERTEX_SHADER_FILEPATH = "hlsl/shader.vert";
const char* FRAGMENT_SHADER_FILEPATH = "hlsl/shader.frag";
const char* TEXTURE0_FILEPATH = "res/karingo.tga";
const char* TEXTURE1_FILEPATH = "res/hunt.tga";

class TestObject : public ISceneObject {
private:
    float rotation = 30.0f;
    // TODO: Do not have these per object basis.
    // Pass in scene and have a resource manager there
    unsigned int vertexBufferObject, vertexArrayObject, EBO;
    Texture* m_loadedTextures[2];
    Shader* _shader;
    const float vertices[180] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
public:
    ~TestObject();
    TestObject();
    void update(unsigned int deltaTime) override;
    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    void position(const glm::vec3& position) { _position = position; }
};

TestObject::~TestObject() {
    unsigned int arr_size = sizeof(m_loadedTextures)/sizeof(m_loadedTextures[0]);
    for(int i = 0; i < arr_size; i++) {
        delete m_loadedTextures[i]; // delete the objects in the array also, who cares rn
    }
}

TestObject::TestObject() {
    _position = glm::vec3(0.0f);
    _shader = new Shader(VERTEX_SHADER_FILEPATH, FRAGMENT_SHADER_FILEPATH);

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &EBO);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture UV in vertice array
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Load textures
    m_loadedTextures[0] = new Texture(TEXTURE0_FILEPATH);
    m_loadedTextures[1] = new Texture(TEXTURE1_FILEPATH);
}

void TestObject::update(unsigned int deltaTime) {};

void TestObject::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    // Bind which VAO OpenGL should use
    glBindVertexArray(vertexArrayObject);
    // Bind textures
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, m_loadedTextures[0]->id());

    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, m_loadedTextures[1]->id());

    // Set active shader and assign textures
    _shader->use();
    _shader->setViewMatrix(viewMatrix);
    _shader->setProjectionMatrix(projectionMatrix);
    _shader->setValue("texture1", 0);
    _shader->setValue("texture2", 1);
    
    float blend = 0.5f * (1.0f + sin(2 * M_PI * 0.1f * glfwGetTime()));
    _shader->setValue("blending", blend);

    // Draw a single box
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    // model = glm::rotate(model, glm::radians(-rotation), glm::vec3(1.0f, 0.0f, 0.0f));
    float rotateY = 360.0f * (1.0f + sin(2.0f * M_PI * 0.2f * glfwGetTime()));
    model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
    _shader->setModelMatrix(model);

    // Draw all triangles
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Undbind VAO and texture from OpenGL
    glBindVertexArray(0);
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