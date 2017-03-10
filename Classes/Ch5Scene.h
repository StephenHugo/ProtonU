#ifndef __CH5_SCENE_H__
#define __CH5_SCENE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch5 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void gotonextScene(float dt);
    
    // ding ding dong! Yaaaaaay! They did it!
    
    void jeffersonAppears(float dt);
    void ringChimes(float dt);
    void setPosNScale(cocos2d::Sprite *sprite, float xx, float yy, float sxx, float syy);
    
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch5);
};

#endif // __CH5_SCENE_H__