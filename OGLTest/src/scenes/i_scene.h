#ifndef I_SCENE_H
#define I_SCENE_H
#include "../objects/i_scene_object.h"
#include "../constants.h"

class IScene {
protected:
//     ISceneObject** _sceneObjectArr;
public:
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};

#endif