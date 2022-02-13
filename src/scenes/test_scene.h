#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "i_scene.h"
#include <glm/glm.hpp>
#include "../objects/i_scene_object.h"
#include "../objects/test_object.h"
#include "../objects/camera.h"
#include "../resource_mgr.h"

// const unsigned int OBJECT_COUNT = 1;
const char* VERTEX_SHADER_FILEPATH = "hlsl/shader.vert";
const char* FRAGMENT_SHADER_FILEPATH = "hlsl/shader.frag";

class TestScene : public IScene {
private:
    // temp
    // protected:
    unsigned int _sceneObjCounter = 0;
    ISceneObject** _sceneObjectArr;
    Camera* _cam;
    Shader* _shader;
    ResourceMgr resourceMgr;

    unsigned int vertexBufferObject, vertexArrayObject, EBO;
public:
    ~TestScene();
    TestScene();
    void update(unsigned int deltaTime);
    void render();
};

TestScene::~TestScene() {
     for (unsigned int i = 0; i < _sceneObjCounter; i++) {
        delete _sceneObjectArr[i];
    }
    delete _sceneObjectArr;
    delete _shader;
    delete _cam;
}

TestScene::TestScene() {
    // TODO: Fix initialization here
    _cam = new Camera(glm::radians(110.0f), WINDOW_WIDTH / WINDOW_HEIGHT);
    int maxX = 32;
    int maxY = 32;
    int maxZ = 32;
    _sceneObjectArr = new ISceneObject*[maxX * maxY * maxZ];
    // _cam->position(glm::vec3(maxX+2.0f, maxY+0.1f, -10.0f));
    _cam->position(glm::vec3(0.0f, 0.0f, -50.0f));
    _cam->lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

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

    _shader = new Shader(VERTEX_SHADER_FILEPATH, FRAGMENT_SHADER_FILEPATH);
    _shader->use();
    _shader->setViewMatrix(_cam->view());
    _shader->setProjectionMatrix(_cam->projection());

    float space = 2.0f;
    for(unsigned int x = 0; x <  maxX; x++) {
        for(unsigned int y = 0; y < maxY; y++) {
            for(unsigned int z = 0; z < maxZ; z++) {
                TestObject* testObj = new TestObject(resourceMgr, _shader);
                testObj->position(glm::vec3(-maxX*space/2 + x*space, -maxY*space/2 + y*space, z*space));
                _sceneObjectArr[_sceneObjCounter] = testObj;
                _sceneObjCounter++;
            }
        }
    }
}

void TestScene::update(unsigned int deltaTime) {
    for (unsigned int i = 0; i < _sceneObjCounter; i++) {
        _sceneObjectArr[i]->update(deltaTime);
    }
}

void TestScene::render() {
    // Bind which VAO OpenGL should use
    glBindVertexArray(vertexArrayObject);

    for (unsigned int i = 0; i < _sceneObjCounter; i++) {
        _sceneObjectArr[i]->render();
    }
    // Undbind VAO and texture from OpenGL
    glBindVertexArray(0);
}

#endif