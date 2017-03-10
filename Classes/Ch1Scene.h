#ifndef __CH1_SCENE_H__
#define __CH1_SCENE_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch1 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void playMusic(float dt);
    
    // call to go to the lobby
    
    void gotonextScene(float dt);
    
    // Jefferson flies around, then explains the frame button functions
    
    void jeffersonAppears(float dt);
    void textAppears(float dt);
    void explanationsAppearNW(float dt);
    void explanationsAppearNE(float dt);
    void explanationsAppearSW(float dt);
    void explanationsAppearSE(float dt);
    
    // Jefferson takes users to the lobby
    void jeffersonReappears(float dt);
    
    // loads the script
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch1);
};

#endif // __CH1_SCENE_H__
