#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "i_scene.h"
#include "../objects/i_scene_object.h"
#include "../objects/test_object.h"

// const unsigned int OBJECT_COUNT = 1;

class TestScene : public IScene {
private:
    // temp
    // protected:
    unsigned int _sceneObjCounter = 0;
    ISceneObject** _sceneObjectArr;
public:
    TestScene();
    void update(unsigned int deltaTime);
    void render();
};

TestScene::TestScene() {
    // TODO: Fix initialization here
    TestObject* testObj = new TestObject();
    _sceneObjectArr = new ISceneObject* { testObj };
    _sceneObjCounter++;
}

void TestScene::update(unsigned int deltaTime) {
    for (unsigned int i = 0; i < _sceneObjCounter; i++) {
        _sceneObjectArr[i]->update(deltaTime);
    }
}

void TestScene::render() {
    for (unsigned int i = 0; i < _sceneObjCounter; i++) {
        _sceneObjectArr[i]->render();
    }
}

#endif