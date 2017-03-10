#ifndef __CH3_SCENE_CALENDAR_H__
#define __CH3_SCENE_CALENDAR_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch3Calendar : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotoChapter4Callback(cocos2d::Ref* pSender);
    void repeatChapter3Callback(cocos2d::Ref* pSender);
    
    // a selector callback
    void gotonextScene(float dt);
    
    // inform patient about things to do around FL during their treatment
    
    void calendarAppears(float dt);
    
    void calendarPage1(float dt);
    
    void calendarPage2(float dt);
    void calendarPage3(float dt);
    void calendarPage4(float dt);
    
    void calendarPage5(float dt);
    void calendarPage6(float dt);
    void calendarPage7(float dt);
    void calendarPage8(float dt);
    
    void calendarPage9(float dt);
    void calendarPage10(float dt);
    void calendarPage11(float dt);
    
    // buttons and explanations appear for Left/right clicking
    
    void finishChapterButtonsAppear(float dt);
    
    void explanationsAppear(float dt);
    
    Json *script;
    
    std::vector<std::string> calendarPages;
    
    int currentPage = 0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch3Calendar);
};

#endif // __CH3_SCENE_CALENDAR_H__
