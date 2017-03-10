#include "CreditsSceneThree.h"
#include "CreditsSceneFour.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

USING_NS_CC;

Scene* Credit3::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Credit3::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Credit3::init()
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
                                           ABOUT3,
                                           ABOUT3,
                                           CC_CALLBACK_1(Credit3::gotomenuCallback, this));
    
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale( visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height );
    
    //// Create the menu, it's an autorelease object
    auto menu = Menu::create(background, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //// go to next scene
    
    this->scheduleOnce(schedule_selector(Credit3::gotonextScene), LAUNCHTRANSITIONTIME);
    
    return true;
}

//// Callback to go to next scene automatically

void Credit3::gotonextScene(float dt)
{
    auto creditsScene = Credit4::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
}

//// Callback for cliking on the menu item

void Credit3::gotomenuCallback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICKSOUND);

    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(CLICKSOUND);

    auto mainMenu = MainMenu::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME*3/4, mainMenu));

}
