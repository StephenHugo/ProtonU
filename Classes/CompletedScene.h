#ifndef __COMPLETED_SCENE_H__
#define __COMPLETED_SCENE_H__

#include "cocos2d.h"

/// This is the first screen of the credits
class Completed : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    /*
     Creates a background as a clickable menu item
     Adds the menu to the scene
     Starts intro music
     Schedules automatic scene transitions
    */

    virtual bool init();
    
    void gotomenuCallback(cocos2d::Ref* pSender);
    /* runs when menu is clicked
     Stops the scheduler
     Stops intro music
     goes to next scene
    */
    
    void playMusic(float dt);
    
    void gotonextScene(float dt);
    /*
     Goes to the next credits scene
    */
    
    // implement the "static create()" method manually
    CREATE_FUNC(Completed);
};

#endif // __COMPLETED_SCENE_H__
