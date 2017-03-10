#include "Ch3SceneCT.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch3SceneCalendar.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch3CT::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch3CT::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch3CT::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    UserDefault * def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 3);
    auto language = def->getStringForKey("LANGUAGE", "english");
    def->flush();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile("scripts/masterscript.txt");
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str());
    script = Json_getItem(chapterScript, "chapter 3");
    
    //// background
    
    auto buildingImage = Sprite::create(CTROOMIMAGE);
    
    buildingImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    buildingImage->setScale( visibleSize.width/buildingImage->getContentSize().width, visibleSize.height/buildingImage->getContentSize().height );
    
    this->addChild(buildingImage,-2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH3);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH3, true);
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNavNoDelay( this );
    
    //// tell the story
    
    auto lagTime = 0.25*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch3CT::childLifeSpecialistAppears), lagTime);
    
    return true;
}

void Ch3CT::gotonextScene(float dt)
{
    
    auto calendarScene = Ch3Calendar::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(2, calendarScene));
}

void Ch3CT::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOCATSCAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOCATSCAN);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*1/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    auto jeffersonImage = Sprite::create(MASKJEFFERSONAFTERNOSHADOWIMAGE);
    
    jeffersonImage->setPosition(Vec2(visibleSize.width*2.9/5 + origin.x,visibleSize.height*2.9/5 + origin.y));
    jeffersonImage->setScale( 0.12*visibleSize.width/jeffersonImage->getContentSize().width, 0.12*visibleSize.width/jeffersonImage->getContentSize().height);
    jeffersonImage->setOpacity(0);
    
    this->addChild(jeffersonImage, -1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH3AUDIOTIMECATSCAN+CH3AUDIOTIMECATSCAN2+CH3AUDIOTIMEFORPEOPLE+CH3AUDIOTIMESMILE+1), FadeOut::create(0.2),nullptr));
    jeffersonImage->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH3AUDIOTIMECATSCAN+CH3AUDIOTIMECATSCAN2+CH3AUDIOTIMEFORPEOPLE+CH3AUDIOTIMESMILE+1), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.13", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMECATSCAN+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMECATSCAN), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3CT::catScan), CH3AUDIOTIMECATSCAN+0.4);
}

void Ch3CT::catScan(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOCATSCAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOCATSCAN2);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOCATSCAN2);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.14", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMECATSCAN2+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMECATSCAN2), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3CT::forPeople), CH3AUDIOTIMECATSCAN2+0.4);
}

void Ch3CT::forPeople(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOCATSCAN2);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOFORPEOPLE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOFORPEOPLE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.15.1", "Go Gators!");
    
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
    
    this->addChild(text, 43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEFORPEOPLE+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEFORPEOPLE), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3CT::smileCamera), CH3AUDIOTIMEFORPEOPLE+0.4);
}

void Ch3CT::smileCamera(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOFORPEOPLE);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOSMILE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOSMILE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.15.2", "Go Gators!");
    auto textString2 = Json_getString(script, "3.15.3", "Go Gators!");
    
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
    
    this->addChild(text, 43);
    this->addChild(text2, 43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMESMILE), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(7*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(7.4*TEMPO), FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMESMILE-7.4*TEMPO), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3CT::gotonextScene), CH3AUDIOTIMESMILE + 0.8);
}