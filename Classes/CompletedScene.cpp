#include "CompletedScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "MainMenuScene.h"
#include "CreditsSceneContact.h"

USING_NS_CC;

Scene* Completed::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Completed::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Completed::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //// Create a background as a menu item
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = MenuItemImage::create(
                                           COMPLETEDPROTONU,
                                           COMPLETEDPROTONU,
                                           CC_CALLBACK_1(Completed::gotomenuCallback, this));
    
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale( visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height );
    
    //// Create the menu, it's an autorelease object
    auto menu = Menu::create(background, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICALMAMATER);
    
        this->scheduleOnce(schedule_selector(Completed::playMusic), 0.4);
    }
    
    //// go to next scene
    
    this->scheduleOnce(schedule_selector(Completed::gotonextScene), 4*LAUNCHTRANSITIONTIME);
    
    return true;
}

void Completed::playMusic(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICALMAMATER, true);
    
}

//// Callback to go to next scene automatically

void Completed::gotonextScene(float dt)
{
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto creditsScene = Contact::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
}

//// Callback for cliking on the menu item

void Completed::gotomenuCallback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    auto mainMenu = MainMenu::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME*3/4, mainMenu));

}
