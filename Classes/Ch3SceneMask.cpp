#include "Ch3SceneMask.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch3SceneCT.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch3Mask::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch3Mask::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch3Mask::init()
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
    
    auto maskImage = Sprite::create(MAKEMASKIMAGE);
    
    maskImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    maskImage->setScale( visibleSize.width/maskImage->getContentSize().width, visibleSize.height/maskImage->getContentSize().height );
    
    this->addChild(maskImage,-2);
    
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
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch3Mask::childLifeSpecialistAppears), lagTime);
    
    lagTime += CH3AUDIOTIMEMAKEMASK + 0.2;
    
    this->scheduleOnce(schedule_selector(Ch3Mask::notMask), lagTime);
    
    lagTime += CH3AUDIOTIMENOTMASK + 0.2;

    this->scheduleOnce(schedule_selector(Ch3Mask::letsPractice), lagTime);
    
    return true;
}

void Ch3Mask::gotonextScene(float dt)
{
    
    auto catScanScene = Ch3CT::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, catScanScene));
}

void Ch3Mask::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOMAKEMASK);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOMAKEMASK);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.7", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEMAKEMASK+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEMAKEMASK), FadeOut::create(0.2), nullptr));
    
    //// add activity sprites
    
    float spriteScale = 0.25;
    
    auto maskOutline = Sprite::create(MASKOUTLINEIMAGE);
    
    maskOutline->setPosition(Vec2(visibleSize.width*1/5 + origin.x,visibleSize.height*2/5 + origin.y));
    maskOutline->setScale( spriteScale*visibleSize.width/maskOutline->getContentSize().width, spriteScale*visibleSize.width/maskOutline->getContentSize().height);
    maskOutline->setOpacity(0);
    
    auto waterImage = Sprite::create(MASKWATERIMAGE);
    
    waterImage->setPosition(Vec2(visibleSize.width*0.97/2 + origin.x,visibleSize.height*2.25/5 + origin.y));
    waterImage->setScale( spriteScale*visibleSize.width/waterImage->getContentSize().width, spriteScale*visibleSize.width/waterImage->getContentSize().height);
    waterImage->setOpacity(0);
    
    auto jeffersonImage = Sprite::create(MASKJEFFERSONBEFOREIMAGE);
    
    jeffersonImage->setPosition(Vec2(visibleSize.width*3.85/5 + origin.x,visibleSize.height*2/5 + origin.y));
    jeffersonImage->setScale( spriteScale*visibleSize.width/jeffersonImage->getContentSize().width, spriteScale*visibleSize.width/jeffersonImage->getContentSize().height);
    jeffersonImage->setOpacity(0);
    
    this->addChild(maskOutline, -1);
    this->addChild(waterImage, -1);
    this->addChild(jeffersonImage, -1);
    
    maskOutline->runAction(FadeIn::create(0.2));
    waterImage->runAction(FadeIn::create(0.2));
    jeffersonImage->runAction(FadeIn::create(0.2));
    
    maskImage = Sprite::create(MASKBEFOREIMAGE);
    
    maskImage->setPosition(Vec2(visibleSize.width*1/5 + origin.x,visibleSize.height*2/5 + origin.y));
    maskImage->setScale( spriteScale*visibleSize.width/maskImage->getContentSize().width, spriteScale*visibleSize.width/maskImage->getContentSize().height);
    maskImage->setOpacity(0);
    maskImage->setRotation(-10);
    
    this->addChild(maskImage, -1);
    
    auto wiggleMask = Sequence::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/5, 20), RotateBy::create(CH1AUDIOTIMEWEEEEE/5, -20),nullptr);
    
    auto wobbleMask = Repeat::create(Sequence::create(ScaleTo::create(CH1AUDIOTIMEWEEEEE/10, spriteScale*1.05*visibleSize.width/maskImage->getContentSize().height, spriteScale*0.95*visibleSize.width/maskImage->getContentSize().height), ScaleTo::create(CH1AUDIOTIMEWEEEEE/10, spriteScale*0.95*visibleSize.width/maskImage->getContentSize().height, spriteScale*1.05*visibleSize.width/maskImage->getContentSize().height), nullptr), 2);
    
    maskImage->runAction(RepeatForever::create(Spawn::create(wiggleMask, wobbleMask, nullptr)));
    
    maskImage->runAction(Sequence::create(DelayTime::create(2), FadeIn::create(0.2), nullptr));
    
}

void Ch3Mask::notMask(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOMAKEMASK);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIONOTMASK);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIONOTMASK);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.8", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMENOTMASK), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMENOTMASK), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3Mask::listenerSetup), CH3AUDIOTIMENOTMASK);
    
}

void Ch3Mask::letsPractice(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIONOTMASK);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOWETNOODLE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOWETNOODLE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.9.1", "Go Gators!");
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMEWETNOODLE), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(9.5*TEMPO), FadeOut::create(0.2), nullptr));
    
}

void Ch3Mask::listenerSetup(float dt)
{
    
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Ch3Mask::onTouchBegan, this, listener, maskImage);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Ch3Mask::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::EventListenerTouchOneByOne *listener, cocos2d::Sprite *sprite)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float spriteScale = 0.25;
    
    if(tapped<1)
    {
        tapped++;
    
        //CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
        //// stop Jefferson from moving around
        sprite->stopAllActions();
    
        //// restore Jefferson to his scale/position
        sprite->runAction(ScaleTo::create(0.2, spriteScale*visibleSize.width/sprite->getContentSize().width, spriteScale*visibleSize.width/sprite->getContentSize().height));
        sprite->setRotation(0);
    
        ccBezierConfig path;
        path.controlPoint_1 = Vec2(visibleSize.width*(0.97/3+2*0.2/3)/2 + origin.x, visibleSize.height*4/5 + origin.y);
        path.controlPoint_2 = Vec2(visibleSize.width*(2*0.97/3+0.2/3)/2 + origin.x, visibleSize.height*4/5 + origin.y);
        path.endPosition = Vec2(Vec2(visibleSize.width*0.97/2 + origin.x, visibleSize.height*2/5 + origin.y));
        auto moveSprite = BezierTo::create(CH1AUDIOTIMEWEEEEE/2 , path);
    
        //// add some spinning!
        auto spinSprite = Repeat::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/4, 540), 2);
        sprite->runAction(Spawn::create(spinSprite, moveSprite, nullptr));
    
    }else if(tapped>0 && tapped<4)
    {
        tapped++;
        auto waterDroplets = Sprite::create(MASKDROPLETSIMAGE);
        
        waterDroplets->setPosition(Vec2(visibleSize.width*0.97/2 + origin.x,visibleSize.height*2.25/5 + origin.y));
        waterDroplets->setScale( 0.75*spriteScale*visibleSize.width/waterDroplets->getContentSize().width, spriteScale*visibleSize.height/waterDroplets->getContentSize().height);
        waterDroplets->setOpacity(0);
        
        this->addChild(waterDroplets);
        
        waterDroplets->runAction(Sequence::create(Spawn::create(FadeIn::create(0.1), MoveBy::create(1.2, Vec2(0, visibleSize.height/15)), ScaleTo::create(1.2, 1.5*spriteScale*visibleSize.width/waterDroplets->getContentSize().width, 0.5*spriteScale*visibleSize.height/waterDroplets->getContentSize().height), nullptr), FadeOut::create(0.1), nullptr));
        
    }else
    {
        
        ccBezierConfig path;
        path.controlPoint_1 = Vec2(visibleSize.width*(0.97/6+2*3.85/15) + origin.x, visibleSize.height*4/5 + origin.y);
        path.controlPoint_2 = Vec2(visibleSize.width*(2*0.97/6+3.85/15) + origin.x, visibleSize.height*4/5 + origin.y);
        path.endPosition = Vec2(Vec2(visibleSize.width*3.85/5 + origin.x, visibleSize.height*2/5 + origin.y));
        auto moveSprite2 = BezierTo::create(CH1AUDIOTIMEWEEEEE/2 , path);
        
        auto spinSprite2 = Repeat::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/4, 540), 2);
        
        sprite->runAction(Sequence::create(Spawn::create(spinSprite2, moveSprite2,nullptr), FadeOut::create(0.2), nullptr));
        
        auto jeffersonImage = Sprite::create(MASKJEFFERSONAFTERIMAGE);
        
        jeffersonImage->setPosition(Vec2(visibleSize.width*3.85/5 + origin.x,visibleSize.height*2/5 + origin.y));
        jeffersonImage->setScale( spriteScale*visibleSize.width/jeffersonImage->getContentSize().width, spriteScale*visibleSize.width/jeffersonImage->getContentSize().height);
        jeffersonImage->setOpacity(0);
        
        this->addChild(jeffersonImage, -1);
        
        jeffersonImage->runAction(Sequence::create(DelayTime::create(CH1AUDIOTIMEWEEEEE/2), FadeIn::create(0.4), nullptr));

        _eventDispatcher->removeEventListener(listener);
        
        this->unscheduleAllCallbacks();
        
        this->scheduleOnce(schedule_selector(Ch3Mask::whileWet), CH1AUDIOTIMEWEEEEE/4 + 4);
    }
    
    return true;
}

void Ch3Mask::whileWet(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOWETNOODLE);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOWHILEWET);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOWHILEWET);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.9.2", "Go Gators!");
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
    
    this->addChild(textBox,43);
    
    this->addChild(text, 44);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMEWHILEWET), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMEWHILEWET), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3Mask::gotonextScene), CH3AUDIOTIMEWHILEWET+1);
    
}