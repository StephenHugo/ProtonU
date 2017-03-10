#ifndef __CH2_SCENE_H__
#define __CH2_SCENE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch2 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotonextScene(float dt);
    
    // bring in the CLS
    
    void childLifeSpecialistAppears(float dt);
    
    // knock on the door
    
    void orangeDoor(float dt);
    void orangeDoorOpens(float dt);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::EventListenerTouchOneByOne *listener);
    
    void highTech(float dt);
    
    // setup the script and check on knocking (clinking events)
    
    Json *script;
    int knocked;

    // implement the "static create()" method manually
    CREATE_FUNC(Ch2);
};

#endif // __CH2_SCENE_H__
