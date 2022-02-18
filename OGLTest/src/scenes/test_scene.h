#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "i_scene.h"
#include <vector>
#include <glm/glm.hpp>
#include "../objects/i_scene_object.h"
#include "../objects/test_object.h"
#include "../objects/camera.h"
#include "../resource_mgr.h"

// const unsigned int OBJECT_COUNT = 1;
const char* OBJECT_VERTEX_SHADER_FILEPATH = "hlsl/basic_shader.vert";
const char* OBJECT_FRAGMENT_SHADER_FILEPATH = "hlsl/basic_shader.frag";

const char* LIGHTSOURCE_VERTEX_SHADER_FILEPATH = "hlsl/basic_lightsource.vert";
const char* LIGHTSOURCE_FRAGMENT_SHADER_FILEPATH = "hlsl/basic_lightsource.frag";

class TestScene : public IScene {
private:
    // temp
    // protected:
    std::vector<ISceneObject*> _sceneObjects;
    std::vector<ISceneObject*> _lightSourceObjects;
    Camera* _cam;
    Shader* _shader;
    Shader* _lightSourceShader;
    ResourceMgr _resourceMgr;

    unsigned int vertexBufferObject, vertexArrayObject, EBO;
    unsigned int lightVAO;
public:
    ~TestScene();
    TestScene();
    void update(float deltaTime);
    void render();
};

TestScene::~TestScene() {
    for (unsigned int i = 0; i < _sceneObjects.size(); i++) {
        delete _sceneObjects[i];
    }
    for (unsigned int i = 0; i < _lightSourceObjects.size(); i++) {
        delete _lightSourceObjects[i];
    }
    delete _shader;
    delete _cam;
}

TestScene::TestScene() {
    // TODO: Fix initialization here
    _cam = new Camera(glm::radians(120.0f), WINDOW_WIDTH / WINDOW_HEIGHT);
    int maxX = 36;
    int maxY = 36;
    int maxZ = 36;
    float spacing = 2.0f;

    // _cam->position(glm::vec3(maxX+2.0f, maxY+0.1f, -10.0f));
    _cam->position(glm::vec3(0.0f, 1.0f, -8.0f));
    _cam->lookAt(glm::vec3(8.0f, 8.0f, 0.0f));

    glGenVertexArrays(1, &vertexArrayObject);
    glGenVertexArrays(1, &lightVAO);

    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &EBO);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture UV in vertice array
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    _shader = new Shader(OBJECT_VERTEX_SHADER_FILEPATH, OBJECT_FRAGMENT_SHADER_FILEPATH);
    _lightSourceShader = new Shader(LIGHTSOURCE_VERTEX_SHADER_FILEPATH, LIGHTSOURCE_FRAGMENT_SHADER_FILEPATH);

    for(unsigned int x = 0; x <  maxX; x++) {
        for(unsigned int y = 0; y < maxY; y++) {
            for(unsigned int z = 0; z < maxZ; z++) {
                TestObject* testObj = new TestObject(_resourceMgr, _shader);
                testObj->position(glm::vec3(x * spacing, y * spacing, z * spacing));
                _sceneObjects.push_back(testObj);
            }
        }
    }

    TestObject* lightSource = new TestObject(_resourceMgr, _lightSourceShader);
    lightSource->position(glm::vec3(1.2f, 1.0f, 2.0f));
    lightSource->scale(0.2f);
    _lightSourceObjects.push_back(lightSource);

 glEnable(GL_CULL_FACE);
}

void TestScene::update(float deltaTime) {
    // for (unsigned int i = 0; i < _sceneObjects.size(); i++) {
    //     _sceneObjects[i]->update(deltaTime);
    // }

    const float radius = 64.0f;
    float x = sin(glfwGetTime() * 2.0f) * radius;
    float z = cos(glfwGetTime() * 2.0f) * radius;
    for (unsigned int i = 0; i < _lightSourceObjects.size(); i++) {
        glm::vec3 pos = _lightSourceObjects[i]->position();
        pos.x = x;
        pos.z = z;
        _lightSourceObjects[i]->position(pos);
    }
}

void TestScene::render() {
    _shader->use();
    _shader->setViewMatrix(_cam->view());
    _shader->setProjectionMatrix(_cam->projection());

    _shader->setValue("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    _shader->setValue("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
    _shader->setValue("lightPosition", _lightSourceObjects[0]->position());
    // Bind which VAO OpenGL should use
    
    glBindVertexArray(vertexArrayObject);
    for (unsigned int i = 0; i < _sceneObjects.size(); i++) {
        _sceneObjects[i]->render();
    }

    glBindVertexArray(lightVAO);
    _lightSourceShader->use();
    _lightSourceShader->setViewMatrix(_cam->view());
    _lightSourceShader->setProjectionMatrix(_cam->projection());

    for (unsigned int i = 0; i < _lightSourceObjects.size(); i++) {
        _lightSourceObjects[i]->render();
    }
    // Undbind VAO and texture from OpenGL
    glBindVertexArray(0);
}

#endif