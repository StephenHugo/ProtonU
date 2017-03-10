#ifndef __CH4_SCENE_DRAG_H__
#define __CH4_SCENE_DRAG_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch4Drag : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotoChapter5Callback(cocos2d::Ref* pSender);
    void repeatChapter4Callback(cocos2d::Ref* pSender);
    
    // a selector callback
    void gotonextScene(float dt);
    
    // go to the next scene if objects were all placed
    
    void jeffersonAppears(float dt);
    
    // buttons and explanations appear for Left/right clicking
    
    void finishChapterButtonsAppear(float dt);
    
    void explanationsAppear(float dt);
    
    Json *script;
    
    // what is currently being moved?
    
    int obj = -1;
    
    // has the object been placed?
    
    std::vector<bool> objFound = {false, false, false, false, false, false};
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch4Drag);
};

#endif // __CH4_SCENE_DRAG_H__
