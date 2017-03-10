#ifndef __CH1INSIDE_SCENE_H__
#define __CH1INSIDE_SCENE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch1Inside : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void gotoChapter2Callback(cocos2d::Ref* pSender);
    void repeatChapter1Callback(cocos2d::Ref* pSender);
    
    // goes to chapter 2
    
    void gotonextScene(float dt);
    
    // Characters apear in the lobby
    
    void jeffersonAppears(float dt);
    void childLifeSpecialistAppears(float dt);
    void radiationText(float dt);
    
    // buttons and explanations appear for Left/right clicking
    
    void finishChapterButtonsAppear(float dt);
    void explanationsAppear(float dt);
    
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch1Inside);
};

#endif // __CH1INSIDE_SCENE_H__
