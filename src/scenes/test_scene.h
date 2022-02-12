#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "i_scene.h"
#include <glm/glm.hpp>
#include "../objects/i_scene_object.h"
#include "../objects/test_object.h"
#include "../objects/camera.h"

// const unsigned int OBJECT_COUNT = 1;

class TestScene : public IScene {
private:
    // temp
    // protected:
    unsigned int _sceneObjCounter = 0;
    ISceneObject** _sceneObjectArr;
    Camera* _cam;
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
}

TestScene::TestScene() {
    // TODO: Fix initialization here
    _cam = new Camera(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT);
    int maxX = 3;
    int maxY = 3;
    int maxZ = 3;
    _sceneObjectArr = new ISceneObject*[maxX * maxY * maxZ];
    _cam->position(glm::vec3(maxX, maxY+5.0f, -10.0f));
    _cam->lookAt(glm::vec3(maxX, maxY, 0.0f));
    for(unsigned int x = 0; x < maxX; x++) {
        for(unsigned int y = 0; y < maxY; y++) {
            for(unsigned int z = 0; z < maxZ; z++) {
                TestObject* testObj = new TestObject();
                testObj->position(glm::vec3(x*2.0f, y*2.0f, z*2.0f));
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
    for (unsigned int i = 0; i < _sceneObjCounter; i++) {
        _sceneObjectArr[i]->render(_cam->view(), _cam->projection());
    }
}

#endif