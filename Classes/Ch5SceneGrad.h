#ifndef __CH5_SCENE_GRAD_H__
#define __CH5_SCENE_GRAD_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch5Grad : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void gotoChapterMenuCallback(cocos2d::Ref* pSender);
    void repeatChapter5Callback(cocos2d::Ref* pSender);
    
    // a selector callback
    void gotonextScene(float dt);
    
    void jeffersonAppears(float dt);
    
    void setPosNScale(cocos2d::Sprite *sprite, float xx, float yy, float sxx, float syy, bool sq, float dt);
    
    // buttons and explanations appear for Left/right clicking
    
    void finishChapterButtonsAppear(float dt);
    
    void explanationsAppear(float dt);
    
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch5Grad);
};

#endif // __CH5_SCENE_GRAD_H__