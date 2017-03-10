#ifndef __CH4_SCENE_H__
#define __CH4_SCENE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch4 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void gotonextScene(float dt);
    
    // set up the explainations of objects in the gantry room
    
    void jeffersonAppears(float dt);
    void childLifeSpecialistAppears(float dt);
    void explainSnout(float dt);
    void explainTable(float dt);
    void explainXrayPanels(float dt);
    void explainCameras(float dt);
    void explainSoundSystem(float dt);
    void jeffersonReappears(float dt);
    
    // transition to the drag-n-drop activity
    
    void childLifeSpecialistReappears(float dt);
    
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch4);
};

#endif // __CH4_SCENE_H__
