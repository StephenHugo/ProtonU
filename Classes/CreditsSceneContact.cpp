#include "CreditsSceneContact.h"
#include "CreditsSceneOne.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

USING_NS_CC;

Scene* Contact::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Contact::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Contact::init()
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
                                           CONTACT,
                                           CONTACT,
                                           CC_CALLBACK_1(Contact::gotomenuCallback, this));
    
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale( visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height );
    
    //// Create the menu, it's an autorelease object
    auto menu = Menu::create(background, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICINTRO);
    }
    
    //// go to next scene
    
    this->scheduleOnce(schedule_selector(Contact::playMusic), 0.4);
    
    return true;
}

void Contact::playMusic(float dt)
{
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICINTRO, true);
    }
    
    this->scheduleOnce(schedule_selector(Contact::gotonextScene), LAUNCHTRANSITIONTIME);
}

//// Callback to go to next scene automatically

void Contact::gotonextScene(float dt)
{
    auto creditsScene = Credit1::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
}

//// Callback for cliking on the menu item

void Contact::gotomenuCallback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICKSOUND);

    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(CLICKSOUND);

    auto mainMenu = MainMenu::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME*3/4, mainMenu));

}
