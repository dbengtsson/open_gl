#ifndef I_SCENE_OBJECT_H
#define I_SCENE_OBJECT_H

class ISceneObject {
protected:
    // virtual ~ISceneObject();
public:
    virtual void update(unsigned int deltaTime) = 0;
    virtual void render() = 0;
};

#endif