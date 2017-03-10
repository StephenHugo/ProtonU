#ifndef __CH3_SCENE_H__
#define __CH3_SCENE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch3 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void gotonextScene(float dt);
    
    // introduce the pillow activity
    
    void childLifeSpecialistAppears(float dt);
    void firstPillow(float dt);
    void letsPractice(float dt);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::EventListenerTouchOneByOne *listener,
                      cocos2d::Sprite *sprite,
                      cocos2d::Sprite *pillowSprite,
                      cocos2d::Sprite *halfpillowSprite,
                      cocos2d::Sprite *deflatedpillowSprite);
    
    void greatPillow(float dt);
    
    Json *script;
    int tapped = 0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch3);
};

#endif // __CH3_SCENE_H__
