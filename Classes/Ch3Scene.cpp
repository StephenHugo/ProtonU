#include "Ch3Scene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch3SceneMask.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch3::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch3::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch3::init()
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
    frameNav.addFrameNav( this );
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch3::childLifeSpecialistAppears), lagTime);
    
    lagTime += CH3AUDIOTIMEWELCOMECT + 0.2;
    
    this->scheduleOnce(schedule_selector(Ch3::firstPillow), lagTime);
    
    lagTime += CH3AUDIOTIMEBEANBAG + 0.2;

    this->scheduleOnce(schedule_selector(Ch3::letsPractice), lagTime);
    
    return true;
}

void Ch3::gotonextScene(float dt)
{
    
    auto maskScene = Ch3Mask::createScene();
    
    Director::getInstance()->pushScene(TransitionCrossFade::create(2, maskScene));
}

void Ch3::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOWELCOMECT);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOWELCOMECT);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*1/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH3AUDIOTIMEWELCOMECT), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.1", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEWELCOMECT+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEWELCOMECT), FadeOut::create(0.2), nullptr));
    
}

void Ch3::firstPillow(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOWELCOMECT);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOBEANBAG);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOBEANBAG);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto pillowBackground = Sprite::create(MAKEPILLOWIMAGE);
    
    pillowBackground->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pillowBackground->setScale( visibleSize.width/pillowBackground->getContentSize().width, visibleSize.height/pillowBackground->getContentSize().height );
    pillowBackground->setOpacity(0);
    
    this->addChild(pillowBackground, -2);
    
    pillowBackground->runAction(FadeIn::create(0.2));
    
    float spriteScale = 0.25;
    
    auto jeffersonOutline = Sprite::create(JEFFERSONOUTLINEIMAGE);
    
    jeffersonOutline->setPosition(Vec2(visibleSize.width*1/5 + origin.x,visibleSize.height*2/5 + origin.y));
    jeffersonOutline->setScale( spriteScale*visibleSize.width/jeffersonOutline->getContentSize().width, spriteScale*visibleSize.width/jeffersonOutline->getContentSize().height);
    jeffersonOutline->setOpacity(0);
    
    auto jeffersonOutline2 = Sprite::create(JEFFERSONOUTLINEIMAGE);
    
    jeffersonOutline2->setPosition(Vec2(visibleSize.width*3.85/5 + origin.x,visibleSize.height*2/5 + origin.y));
    jeffersonOutline2->setScale( spriteScale*visibleSize.width/jeffersonOutline2->getContentSize().width, spriteScale*visibleSize.width/jeffersonOutline2->getContentSize().height);
    jeffersonOutline2->setOpacity(0);
    
    this->addChild(jeffersonOutline,-1);
    this->addChild(jeffersonOutline2,-1);
    
    jeffersonOutline->runAction(FadeIn::create(0.2));
    jeffersonOutline2->runAction(FadeIn::create(0.2));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.2.1", "Go Gators!");
    auto textString2 = Json_getString(script, "3.2.2", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEBEANBAG-0.2), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(6.4*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(6.8*TEMPO), FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEBEANBAG-7*TEMPO), FadeOut::create(0.2), nullptr));
    
}

void Ch3::letsPractice(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOBEANBAG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOPRACTICEPILLOW);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOPRACTICEPILLOW);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.3", "Go Gators!");
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMEPRACTICEPILLOW), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMEPRACTICEPILLOW), FadeOut::create(0.2), nullptr));
    
    //// add activity sprites
    
    float spriteScale = 0.25;
    
    auto defaultPillow = Sprite::create(PILLOWIMAGE);
    
    defaultPillow->setPosition(Vec2(visibleSize.width*0.97/2 + origin.x,visibleSize.height*2/5 + origin.y));
    defaultPillow->setScale( spriteScale*visibleSize.width/defaultPillow->getContentSize().width, spriteScale*visibleSize.width/defaultPillow->getContentSize().height);
    defaultPillow->setOpacity(0);
    
    this->addChild(defaultPillow,-1);
    
    defaultPillow->runAction(FadeIn::create(0.2));
    
    //// add other pillow sprites
    
    auto halfPillow = Sprite::create(PILLOWHALFIMAGE);
    
    halfPillow->setPosition(Vec2(visibleSize.width*0.97/2 + origin.x,visibleSize.height*2/5 + origin.y));
    halfPillow->setScale( 0.9*spriteScale*visibleSize.width/halfPillow->getContentSize().width, 0.9*spriteScale*visibleSize.width/halfPillow->getContentSize().height);
    halfPillow->setOpacity(0);
    
    auto deflatedPillow = Sprite::create(PILLOWDEFLATEDIMAGE);
    
    deflatedPillow->setPosition(Vec2(visibleSize.width*0.97/2 + origin.x,visibleSize.height*2/5 + origin.y));
    deflatedPillow->setScale( 0.9*spriteScale*visibleSize.width/deflatedPillow->getContentSize().width, 0.9*spriteScale*visibleSize.width/deflatedPillow->getContentSize().height);
    deflatedPillow->setOpacity(0);
    
    this->addChild(halfPillow,-1);
    this->addChild(deflatedPillow,-1);
    
    //// create interactive Jefferson sprite
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*1/5 + origin.x,visibleSize.height*2/5 + origin.y));
    jefferson->setScale( spriteScale*visibleSize.width/jefferson->getContentSize().width, spriteScale*visibleSize.width/jefferson->getContentSize().height);
    jefferson->setRotation(-10);
    jefferson->setOpacity(0);
    
    this->addChild(jefferson,-1);
    
    auto wiggleJefferson = Sequence::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/5, 20), RotateBy::create(CH1AUDIOTIMEWEEEEE/5, -20),nullptr);
    
    auto wobbleJefferson = Repeat::create(Sequence::create(ScaleTo::create(CH1AUDIOTIMEWEEEEE/10, spriteScale*1.05*visibleSize.width/jefferson->getContentSize().height, spriteScale*0.95*visibleSize.width/jefferson->getContentSize().height), ScaleTo::create(CH1AUDIOTIMEWEEEEE/10, spriteScale*0.95*visibleSize.width/jefferson->getContentSize().height, spriteScale*1.05*visibleSize.width/jefferson->getContentSize().height), nullptr), 2);
    
    jefferson->runAction(Sequence::create(DelayTime::create(0.2), FadeIn::create(0.2), nullptr));
    
    jefferson->runAction(RepeatForever::create(Spawn::create(wiggleJefferson, wobbleJefferson, nullptr)));
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    listener->onTouchBegan = CC_CALLBACK_2(Ch3::onTouchBegan, this, listener, jefferson, defaultPillow, halfPillow, deflatedPillow);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool Ch3::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::EventListenerTouchOneByOne *listener, cocos2d::Sprite *sprite, cocos2d::Sprite *pillowSprite, cocos2d::Sprite *halfpillowSprite, cocos2d::Sprite *deflatedpillowSprite)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float spriteScale = 0.25;
    
    if(tapped<1)
    {
        tapped++;
    
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIOWEEEEEEEE);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOWEEEEEEEE);
    
        //// stop Jefferson from moving around
        sprite->stopAllActions();
    
        //// restore Jefferson to his scale/position
        sprite->runAction(ScaleTo::create(0.2, spriteScale*visibleSize.width/sprite->getContentSize().width, spriteScale*visibleSize.width/sprite->getContentSize().height));
        sprite->setRotation(0);
    
        ccBezierConfig path;
        path.controlPoint_1 = Vec2(visibleSize.width*(0.97/3+2*0.2/3)/2 + origin.x, visibleSize.height*4/5 + origin.y);
        path.controlPoint_2 = Vec2(visibleSize.width*(2*0.97/3+0.2/3)/2 + origin.x, visibleSize.height*4/5 + origin.y);
        path.endPosition = Vec2(Vec2(visibleSize.width*0.97/2 + origin.x, visibleSize.height*2/5 + origin.y));
        auto moveSprite = BezierTo::create(CH1AUDIOTIMEWEEEEE , path);
    
        //// add some spinning!
        auto spinSprite = Repeat::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/2, 540), 2);
        sprite->runAction(Spawn::create(spinSprite, moveSprite, nullptr));
    
    }else if(tapped>0 && tapped<3)
    {
        tapped++;
        
        pillowSprite->runAction(Repeat::create(Sequence::create(ScaleTo::create(0.15, spriteScale*1.05*visibleSize.width/pillowSprite->getContentSize().height, spriteScale*0.95*visibleSize.width/pillowSprite->getContentSize().height), ScaleTo::create(0.15, spriteScale*0.95*visibleSize.width/pillowSprite->getContentSize().height, spriteScale*1.05*visibleSize.width/pillowSprite->getContentSize().height), nullptr), 2));
    }else if(tapped>2 && tapped<4)
    {
        tapped++;
        
        pillowSprite->runAction(Spawn::create(ScaleTo::create(0.15, spriteScale*0.90*visibleSize.width/pillowSprite->getContentSize().height, spriteScale*0.90*visibleSize.width/pillowSprite->getContentSize().height), FadeOut::create(0.2), nullptr));
        halfpillowSprite->runAction(Sequence::create(Spawn::create(FadeIn::create(0.3) ,ScaleTo::create(0.15, spriteScale*visibleSize.width/halfpillowSprite->getContentSize().height, spriteScale*visibleSize.width/halfpillowSprite->getContentSize().height), nullptr), ScaleTo::create(0.15, spriteScale*0.95*visibleSize.width/halfpillowSprite->getContentSize().height, spriteScale*1.05*visibleSize.width/halfpillowSprite->getContentSize().height), nullptr));
    }else if(tapped>3 && tapped<6)
    {
        tapped++;
        
        halfpillowSprite->runAction(Repeat::create(Sequence::create(ScaleTo::create(0.15, spriteScale*1.05*visibleSize.width/halfpillowSprite->getContentSize().height, spriteScale*0.95*visibleSize.width/halfpillowSprite->getContentSize().height), ScaleTo::create(0.15, spriteScale*0.95*visibleSize.width/halfpillowSprite->getContentSize().height, spriteScale*1.05*visibleSize.width/halfpillowSprite->getContentSize().height), nullptr), 2));
    }else if(tapped>5 && tapped<7)
    {
        tapped++;
        
        halfpillowSprite->runAction(Spawn::create(ScaleTo::create(0.15, spriteScale*0.90*visibleSize.width/halfpillowSprite->getContentSize().height, spriteScale*0.90*visibleSize.width/halfpillowSprite->getContentSize().height), FadeOut::create(0.2), nullptr));
        deflatedpillowSprite->runAction(Sequence::create(Spawn::create(FadeIn::create(0.3) ,ScaleTo::create(0.15, 1.05*spriteScale*visibleSize.width/deflatedpillowSprite->getContentSize().height, 1.05*spriteScale*visibleSize.width/deflatedpillowSprite->getContentSize().height), nullptr), ScaleTo::create(0.15, spriteScale*visibleSize.width/deflatedpillowSprite->getContentSize().height, spriteScale*visibleSize.width/deflatedpillowSprite->getContentSize().height), nullptr));
    }else
    {
        this->removeChild(pillowSprite);
        this->removeChild(halfpillowSprite);
        
        ccBezierConfig path;
        path.controlPoint_1 = Vec2(visibleSize.width*(0.97/6+2*3.85/15) + origin.x, visibleSize.height*4/5 + origin.y);
        path.controlPoint_2 = Vec2(visibleSize.width*(2*0.97/6+3.85/15) + origin.x, visibleSize.height*4/5 + origin.y);
        path.endPosition = Vec2(Vec2(visibleSize.width*3.85/5 + origin.x, visibleSize.height*2/5 + origin.y));
        auto moveSprite2 = BezierTo::create(CH1AUDIOTIMEWEEEEE , path);
        
        auto spinSprite2 = Repeat::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/2, 540), 2);
        sprite->runAction(Spawn::create(spinSprite2, moveSprite2,nullptr));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOWEEEEEEEE);
        
        auto wiggleJefferson = Sequence::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/5, 20), RotateBy::create(CH1AUDIOTIMEWEEEEE/5, -20),nullptr);
        
        auto wobbleJefferson = Repeat::create(Sequence::create(ScaleTo::create(CH1AUDIOTIMEWEEEEE/10, spriteScale*1.05*visibleSize.width/sprite->getContentSize().height, spriteScale*0.95*visibleSize.width/sprite->getContentSize().height), ScaleTo::create(CH1AUDIOTIMEWEEEEE/10, spriteScale*0.95*visibleSize.width/sprite->getContentSize().height, spriteScale*1.05*visibleSize.width/sprite->getContentSize().height), nullptr), 2);
        
        deflatedpillowSprite->setRotation(-10);
        deflatedpillowSprite->runAction(RepeatForever::create(Spawn::create(wiggleJefferson, wobbleJefferson, nullptr)));

        _eventDispatcher->removeEventListener(listener);
        
        this->unscheduleAllCallbacks();
        
        this->scheduleOnce(schedule_selector(Ch3::greatPillow), CH1AUDIOTIMEWEEEEE + 1);
    }
    
    return true;
}

void Ch3::greatPillow(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIOWEEEEEEEE);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOSPECIALPILLOW);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOSPECIALPILLOW);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textString = Json_getString(script, "3.6.1", "Go Gators!");
    auto textString2 = Json_getString(script, "3.6.2", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMESPECIALPILLOW), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(6.4*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(6.8*TEMPO), FadeIn::create(0.4), DelayTime::create(CH3AUDIOTIMESPECIALPILLOW - 6.8*TEMPO), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch3::gotonextScene), CH3AUDIOTIMESPECIALPILLOW + 0.4);
}