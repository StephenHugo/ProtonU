#ifndef __CH3_SCENE_CT_H__
#define __CH3_SCENE_CT_H__

#include "cocos2d.h"
#include "spine/json.h"

class Ch3CT : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void gotonextScene(float dt);
    
    // explain the CAT scan
    
    void childLifeSpecialistAppears(float dt);
    
    void catScan(float dt);
    void forPeople(float dt);
    void smileCamera(float dt);
    
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ch3CT);
};

#endif // __CH3_SCENE_CT_H__
