#include "LaunchScene.h"
#include "CreditsSceneContact.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "FrameStuff.h"

USING_NS_CC;

Scene* Launch::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Launch::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Launch::init()
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
                                           LAUNCHIMAGE,
                                           LAUNCHIMAGE,
                                           CC_CALLBACK_1(Launch::gotomenuCallback, this));
    
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale( visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height );
    
    //// Create the menu, it's an autorelease object
    auto menu = Menu::create(background, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //// Begin music!
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICINTRO);
    
    this->scheduleOnce(schedule_selector(Launch::playMusic), 4);
    
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    return true;
}

void Launch::playMusic(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICINTRO, true);
    
    this->scheduleOnce(schedule_selector(Launch::gotonextScene), LAUNCHTRANSITIONTIME);
}

//// Callback to go to next scene automatically

void Launch::gotonextScene(float dt)
{
    auto creditsScene = Contact::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
}

//// Callback for lciking on the menu item

void Launch::gotomenuCallback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    auto mainMenu = MainMenu::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME*3/4, mainMenu));

}
