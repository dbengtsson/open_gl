#ifndef I_SCENE_H
#define I_SCENE_H
#include "../objects/i_scene_object.h"

class IScene {
protected:
//     ISceneObject** _sceneObjectArr;
public:
    virtual void update(unsigned int deltaTime) = 0;
    virtual void render() = 0;
};

#endif