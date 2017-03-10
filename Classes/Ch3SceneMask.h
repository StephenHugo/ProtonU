#ifndef __CH3_SCENE_MASK_H__
#define __CH3_SCENE_MASK_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch3Mask : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotonextScene(float dt);
    
    // introduce the mask activity
    
    void childLifeSpecialistAppears(float dt);
    void notMask(float dt);
    void letsPractice(float dt);
    void whileWet(float dt);
    void listenerSetup(float dt);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::EventListenerTouchOneByOne *listener,
                      cocos2d::Sprite *sprite);
    
    Json *script;
    int tapped = 0;
    cocos2d::Sprite *maskImage;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch3Mask);
};

#endif // __CH3_SCENE_MASK_H__
