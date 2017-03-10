#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // this callback returns users to the scrolling credits
    
    void creditsCallback(Ref* pSender);

    // resume the last chapter visited from the beginning
    
    void resumeCallback(Ref* pSender);
    
    // go to that chapter, start at the beginning
    
    void ch1Callback(Ref* pSender);
    void ch2Callback(Ref* pSender);
    void ch3Callback(Ref* pSender);
    void ch4Callback(Ref* pSender);
    void ch5Callback(Ref* pSender);
    
    void setPosNScale(cocos2d::MenuItemImage *sprite, float xx, float yy, float sxx, float syy);
    
    // exit the app
    void exitCallback(cocos2d::Ref* pSender);
    
    void gotoCreditsScene(float dt);
    /*
     Goes to the credits scene
     */
    
    void playMusic(float dt);
    
    void gotoLaunchScene(float dt);
    /*
     Goes to the launch scene
     */
    
    void exitDialogue(float dt);
    
    void toggleLanguage(cocos2d::Ref* pSender, int lang);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
