#include "FrameStuff.h"
#include "LaunchScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

USING_NS_CC;

Scene* FrameNav::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FrameNav::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool FrameNav::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //// code
    
    //// go back to launch screen
    
    this->scheduleOnce(schedule_selector(FrameNav::gotonextScene), LAUNCHTRANSITIONTIME);
    
    //// preload sound effects
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICKSOUND);
    
    //// listen for clicks
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FrameNav::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    ////
    
    return true;
}

bool FrameNav::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CLICKSOUND);
    
    return true;
}

void FrameNav::gotonextScene(float dt)
{
    auto launchScene = Launch::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(2, launchScene));
}
