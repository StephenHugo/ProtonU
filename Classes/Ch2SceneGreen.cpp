#include "Ch2SceneGreen.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch2SceneBlue.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch2Green::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch2Green::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch2Green::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    UserDefault * def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "english");
    def->flush();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile("scripts/masterscript.txt");
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str());
    script = Json_getItem(chapterScript, "chapter 2");
    
    //// background
    
    auto buildingImage = Sprite::create(HALLWAYIMAGE);
    
    buildingImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    buildingImage->setScale( visibleSize.width/buildingImage->getContentSize().width, visibleSize.height/buildingImage->getContentSize().height );
    
    this->addChild(buildingImage, -2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH2);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH2, true);
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNavNoDelay( this );
    
    //// tell the story
    
    auto lagTime = 0.2;
    
    this->scheduleOnce(schedule_selector(Ch2Green::childLifeSpecialistAppears), lagTime);
    
    lagTime = 0.2 + CH2AUDIOTIMEMEETSOCIALWORKER + 0.6;
    
    this->scheduleOnce(schedule_selector(Ch2Green::greenDoor), lagTime);

    return true;
}

void Ch2Green::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    auto nextScene = Ch2Blue::createScene();
    
    Director::getInstance()->pushScene(TransitionCrossFade::create(0.4, nextScene));
}

void Ch2Green::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIOMEETSOCIALWORKER);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIOMEETSOCIALWORKER);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*2/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMEMEETSOCIALWORKER), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.5", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    text->setColor(cocos2d::Color3B::BLACK);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*1.85/20 + origin.y));
    textBox->setScale( 0.65*visibleSize.width/textBox->getContentSize().width, 0.25*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEMEETSOCIALWORKER), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEMEETSOCIALWORKER), FadeOut::create(0.2), nullptr));
    
}

void Ch2Green::greenDoor(float dt)
{
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIOMEETSOCIALWORKER);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(KNOCKSOUND);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto greenClosed = Sprite::create(GREENDOORCLOSED);
    
    greenClosed->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    greenClosed->setScale( visibleSize.width/greenClosed->getContentSize().width, visibleSize.height/greenClosed->getContentSize().height );
    
    this->addChild(greenClosed, -2);
    
    greenClosed->setOpacity(0);
    greenClosed->runAction(FadeIn::create(0.2));
    
    knocked = 0;
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Ch2Green::onTouchBegan, this, listener);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool Ch2Green::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::EventListenerTouchOneByOne *listener)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(KNOCKSOUND);
    
    knocked++;
    if(knocked>1.5)
    {
        knocked = 0;
        _eventDispatcher->removeEventListener(listener);
        this->unscheduleAllCallbacks();
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        auto greenOpened = Sprite::create(GREENDOOROPEN);
        
        greenOpened->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        greenOpened->setScale( visibleSize.width/greenOpened->getContentSize().width, visibleSize.height/greenOpened->getContentSize().height );
        
        this->addChild(greenOpened, -2);
        
        greenOpened->setOpacity(0);
        greenOpened->runAction(Sequence::create(DelayTime::create(LAUNCHTRANSITIONTIME*0.2),FadeIn::create(0.2), nullptr));
        this->scheduleOnce(schedule_selector(Ch2Green::greenDoorOpens), LAUNCHTRANSITIONTIME*0.25);
    }
    
    return true;
}

void Ch2Green::greenDoorOpens(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIOSOCIALWORKER);
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIOMEETSOCIALWORKER);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIOSOCIALWORKER);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    ////
    
    auto socialWorker = Sprite::create(SOCIALWORKERIMAGE);
    
    socialWorker->setPosition(Vec2(visibleSize.width*3/5 + origin.x,visibleSize.height*2/5 + origin.y));
    socialWorker->setScale( 0.3*visibleSize.width/socialWorker->getContentSize().width, 0.75*visibleSize.height/socialWorker->getContentSize().height);
    
    this->addChild(socialWorker,-1);
    
    socialWorker->setOpacity(0);
    
    socialWorker->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMESOCIALWORKER), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.6.1", "Go Gators!");
    auto textString2 = Json_getString(script, "2.6.2", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    text->setColor(cocos2d::Color3B::BLACK);
    text->setOpacity(0);
    
    auto text2 = Label::createWithTTF(textString2, FELTFONT, visibleSize.height*TEXTSIZE);
    text2->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text2->setWidth(0.6*visibleSize.width);
    text2->setHeight(visibleSize.height*3.2/20);
    text2->setColor(cocos2d::Color3B::BLACK);
    text2->setOpacity(0);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*1.85/20 + origin.y));
    textBox->setScale( 0.65*visibleSize.width/textBox->getContentSize().width, 0.25*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    this->addChild(text2,43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMESOCIALWORKER), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(7.6*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(8*TEMPO),FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMESOCIALWORKER-8*TEMPO), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch2Green::gotonextScene), CH2AUDIOTIMESOCIALWORKER+0.8);
}