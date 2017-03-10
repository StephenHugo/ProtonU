#include "Ch2Scene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch2SceneGreen.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch2::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch2::init()
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
    frameNav.addFrameNav( this );
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch2::childLifeSpecialistAppears), lagTime);
    
    lagTime = 0.5*LAUNCHTRANSITIONTIME + 0.2 + CH2AUDIOTIMEMEETRADTHERAPIST + 0.8;
    
    this->scheduleOnce(schedule_selector(Ch2::orangeDoor), lagTime);

    return true;
}

void Ch2::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    auto nextScene = Ch2Green::createScene();
    
    Director::getInstance()->pushScene(TransitionCrossFade::create(0.4, nextScene));
}

void Ch2::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIOMEETRADTHERAPIST);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIOMEETRADTHERAPIST);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*1/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMEMEETRADTHERAPIST), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.1", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEMEETRADTHERAPIST), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEMEETRADTHERAPIST), FadeOut::create(0.2), nullptr));
    
    auto orangeClosed = Sprite::create(ORANGEDOORCLOSED);
    
    orangeClosed->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    orangeClosed->setScale( visibleSize.width/orangeClosed->getContentSize().width, visibleSize.height/orangeClosed->getContentSize().height );
    
    this->addChild(orangeClosed, -2);
    
    orangeClosed->setOpacity(0);
    orangeClosed->runAction(Sequence::create(DelayTime::create(CH2AUDIOTIMEMEETRADTHERAPIST+0.4), FadeIn::create(0.2), nullptr));
    
}

void Ch2::orangeDoor(float dt)
{
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIOMEETRADTHERAPIST);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIOTAP2);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIOTAP2);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMETAP2), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.2", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    text->setColor(cocos2d::Color3B::BLACK);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*1.85/20 + origin.y));
    textBox->setScale( 0.65*visibleSize.width/textBox->getContentSize().width, 0.25*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMETAP2), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMETAP2), FadeOut::create(0.2), nullptr));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(KNOCKSOUND);
    
    knocked = 0;
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Ch2::onTouchBegan, this, listener);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool Ch2::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::EventListenerTouchOneByOne *listener)
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
        
        auto orangeOpened = Sprite::create(ORANGEDOOROPEN);
        
        orangeOpened->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        orangeOpened->setScale( visibleSize.width/orangeOpened->getContentSize().width, visibleSize.height/orangeOpened->getContentSize().height );
        
        this->addChild(orangeOpened, -2);
        
        orangeOpened->setOpacity(0);
        orangeOpened->runAction(Sequence::create(DelayTime::create(LAUNCHTRANSITIONTIME*0.2),FadeIn::create(0.2), nullptr));
        this->scheduleOnce(schedule_selector(Ch2::orangeDoorOpens), LAUNCHTRANSITIONTIME*0.25);
    }
    
    return true;
}

void Ch2::orangeDoorOpens(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIORADTHERAPIST);
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIOTAP2);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIORADTHERAPIST);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    ////
    
    auto radTherapist = Sprite::create(THERAPISTIMAGE);
    
    radTherapist->setPosition(Vec2(visibleSize.width*2/5 + origin.x,visibleSize.height*2/5 + origin.y));
    radTherapist->setScale( 0.3*visibleSize.width/radTherapist->getContentSize().width, 0.75*visibleSize.height/radTherapist->getContentSize().height);
    
    this->addChild(radTherapist,-1);
    
    radTherapist->setOpacity(0);
    
    radTherapist->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMERADTHERAPIST+CH2AUDIOTIMEHIGHTECH+0.4), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.3.1", "Go Gators!");
    auto textString2 = Json_getString(script, "2.3.2", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMERADTHERAPIST), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(2*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(2.4*TEMPO),FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMERADTHERAPIST-2.4*TEMPO), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch2::highTech), CH2AUDIOTIMERADTHERAPIST+0.4);
}

void Ch2::highTech(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIORADTHERAPIST);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIOHIGHTECH);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIOHIGHTECH);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMEHIGHTECH), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.4", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    text->setColor(cocos2d::Color3B::BLACK);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*1.85/20 + origin.y));
    textBox->setScale( 0.65*visibleSize.width/textBox->getContentSize().width, 0.25*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEHIGHTECH), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEHIGHTECH), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch2::gotonextScene), CH2AUDIOTIMEHIGHTECH+0.8);
}
