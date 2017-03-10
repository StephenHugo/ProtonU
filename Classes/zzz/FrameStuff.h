#ifndef __FRAME_NAV_H__
#define __FRAME_NAV_H__

#include "cocos2d.h"

class FrameNav : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
    void gotonextScene(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(FrameNav);
};

#endif // __FRAME_NAV_H__
