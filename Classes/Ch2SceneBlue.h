#ifndef __CH2_SCENE_BLUE_H__
#define __CH2_SCENE_BLUE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch2Blue : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotoChapter3Callback(cocos2d::Ref* pSender);
    void repeatChapter2Callback(cocos2d::Ref* pSender);
    
    void gotonextScene(float dt);
    
    void childLifeSpecialistAppears(float dt);
    
    // open up the blue door
    
    void blueDoor(float dt);
    void blueDoorOpens(float dt);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::EventListenerTouchOneByOne *listener);
    
    void doctorAppears(float dt);
    void andNurse(float dt);
    
    // buttons and explanations appear for Left/right clicking
    
    void finishChapterButtonsAppear(float dt);
    
    void explanationsAppear(float dt);
    
    // script and click handling again
    
    Json *script;
    int knocked;

    // implement the "static create()" method manually
    CREATE_FUNC(Ch2Blue);
};

#endif // __CH2_SCENE_BLUE_H__
