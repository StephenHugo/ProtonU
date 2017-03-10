#ifndef __CH2_SCENE_GREEN_H__
#define __CH2_SCENE_GREEN_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch2Green : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotonextScene(float dt);
    
    void childLifeSpecialistAppears(float dt);
    
    // open the green door
    
    void greenDoor(float dt);
    void greenDoorOpens(float dt);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::EventListenerTouchOneByOne *listener);
    
    // script + click events
    
    Json *script;
    int knocked;

    // implement the "static create()" method manually
    CREATE_FUNC(Ch2Green);
};

#endif // __CH2_SCENE_GREEN_H__
