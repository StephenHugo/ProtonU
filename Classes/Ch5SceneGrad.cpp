#include "Ch5SceneGrad.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch5Scene.h"
#include "CompletedScene.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

#include <cmath>
#include <cstdlib>

USING_NS_CC;

Scene* Ch5Grad::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch5Grad::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch5Grad::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    UserDefault * def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 5);
    auto language = def->getStringForKey("LANGUAGE", "english");
    def->flush();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile("scripts/masterscript.txt");
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str());
    script = Json_getItem(chapterScript, "chapter 5");
    
    //// background
    
    auto lobbyImage = Sprite::create(LOBBYIMAGE);
    
    lobbyImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    lobbyImage->setScale( visibleSize.width/lobbyImage->getContentSize().width, visibleSize.height/lobbyImage->getContentSize().height );
    
    this->addChild(lobbyImage, -1);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICALMAMATER);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICALMAMATER, true);
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNavNoDelay( this );
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME/4;
    
    this->scheduleOnce(schedule_selector(Ch5Grad::jeffersonAppears), lagTime);
    
    return true;
}

void Ch5Grad::gotoChapterMenuCallback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto menuScene = Completed::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, menuScene));
    
}

void Ch5Grad::repeatChapter5Callback(Ref* pSender)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch5Scene = Ch5::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch5Scene));
    
}

void Ch5Grad::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    auto dragScene = Completed::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(0.2, dragScene));
}

void Ch5Grad::jeffersonAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH5AUDIOHERETOHELP);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH5AUDIOHERETOHELP);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// add all of the team!
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    auto childLifeSpecialist = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    auto doctor = Sprite::create(DOCIMAGE);
    auto nurse = Sprite::create(NURSE1IMAGE);
    auto socialWorker = Sprite::create(SOCIALWORKERIMAGE);
    auto radTherapist = Sprite::create(THERAPISTIMAGE);
    
    float center = 0.48f;
    float spacing = 0.16f;
    this->setPosNScale(nurse, center - spacing*2, 0.3, 0.25, 0.6, false, 0.45);
    this->setPosNScale(doctor , center - spacing, 0.29, 0.25, 0.6, false, 0.4);
    this->setPosNScale(socialWorker, center + spacing*2, 0.31, 0.25, 0.6, false, 0.35);
    this->setPosNScale(radTherapist, center + spacing, 0.3, 0.25, 0.6, false, 0.3);
    this->setPosNScale(childLifeSpecialist, center, 0.305, 0.25, 0.6, false, 0.25);
    this->setPosNScale(jefferson, 0.85, 0.2, 0.35, 0.35, true, 0.2);
    
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "5.3", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH5AUDIOTIMEHERETOHELP), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH5AUDIOTIMEHERETOHELP), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch5Grad::finishChapterButtonsAppear), 2.4*TEMPO + CH5AUDIOTIMEHERETOHELP);
    
}

void Ch5Grad::setPosNScale(cocos2d::Sprite *sprite, float xx, float yy, float sxx, float syy, bool sq, float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width*xx + origin.x, visibleSize.height*yy + origin.y));
    
    sprite->setScale( sxx*visibleSize.width/sprite->getContentSize().width, syy*visibleSize.height/sprite->getContentSize().height);
    
    if (sq)
    {
        sprite->setScale( sxx*visibleSize.width/sprite->getContentSize().width, syy*visibleSize.width/sprite->getContentSize().height);
    }

    sprite->setOpacity(0);
    
    this->addChild(sprite, -1);
    
    sprite->runAction(FadeIn::create(dt));
}

void Ch5Grad::finishChapterButtonsAppear(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH3AUDIOAFTERCT);
    
    FrameNav frameNav;
    frameNav.addFrameNav( this );
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    //// Create finish chapter/go back buttons for the frame
    
    auto gotoChapter3 = MenuItemImage::create(
                                              NAVRIGHTON,
                                              NAVRIGHTOFF,
                                              CC_CALLBACK_1(Ch5Grad::gotoChapterMenuCallback, this));
    
    gotoChapter3->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height/2 + origin.y));
    gotoChapter3->setScale( 0.1*visibleSize.width/gotoChapter3->getContentSize().width, 0.2*visibleSize.width/gotoChapter3->getContentSize().height );
    
    auto repeatChapter2 = MenuItemImage::create(
                                                NAVLEFTON,
                                                NAVLEFTOFF,
                                                CC_CALLBACK_1(Ch5Grad::repeatChapter5Callback, this));
    
    repeatChapter2->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height/2 + origin.y));
    repeatChapter2->setScale( 0.1*visibleSize.width/repeatChapter2->getContentSize().width, 0.2*visibleSize.width/repeatChapter2->getContentSize().height );
    
    
    // create menu, it's an autorelease object
    auto frameButtons = Menu::create(gotoChapter3, repeatChapter2, NULL);
    frameButtons->setPosition(Vec2::ZERO);
    frameButtons->setOpacity(0);
    
    this->addChild(frameButtons, 1);
    
    auto appear = FadeIn::create(0.2);
    frameButtons->runAction(appear);
    
    this->scheduleOnce(schedule_selector(Ch5Grad::explanationsAppear), 0.2);
    
    this->scheduleOnce(schedule_selector(Ch5Grad::gotonextScene), 2*LAUNCHTRANSITIONTIME);
    
}

void Ch5Grad::explanationsAppear(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textString = Json_getString(script, "clickLeft", "Go Gators!");
    
    //// begin explanations of the NW frame button
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.29 + origin.x, visibleSize.height*0.3 + origin.y));
    text->setWidth(0.41*visibleSize.width);
    text->setHeight(visibleSize.height*0.25);
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(BUBBLENWIMAGE);
    
    textBox->setPosition(Vec2(visibleSize.width*0.27 + origin.x, visibleSize.height*0.36 + origin.y));
    textBox->setScale( 0.45*visibleSize.width/textBox->getContentSize().width, 0.23*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    auto textString2 = Json_getString(script, "clickRight", "Go Gators!");
    
    //// begin explanations of the NW frame button
    
    auto text2 = Label::createWithTTF(textString2, FELTFONT, visibleSize.height*TEXTSIZE);
    text2->setPosition(Vec2(visibleSize.width*0.73 + origin.x, visibleSize.height*0.3 + origin.y));
    text2->setWidth(0.41*visibleSize.width);
    text2->setHeight(visibleSize.height*0.25);
    text2->setColor(cocos2d::Color3B::WHITE);
    text2->setOpacity(0);
    
    auto textBox2 = Sprite::create(BUBBLENEIMAGE);
    
    textBox2->setPosition(Vec2(visibleSize.width*0.73 + origin.x, visibleSize.height*0.36 + origin.y));
    textBox2->setScale( 0.45*visibleSize.width/textBox2->getContentSize().width, 0.23*visibleSize.height/textBox2->getContentSize().height );
    
    textBox2->setOpacity(0);
    
    this->addChild(textBox2,42);
    
    this->addChild(text2,43);
    
    auto appear = FadeIn::create(0.2);
    textBox2->runAction(Sequence::create(appear, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text2->runAction(Sequence::create(appear2, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    
    auto appear3 = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(DelayTime::create(EXPLAINFRAMEBUTTONSTIME+0.4), appear3, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    auto appear4 = FadeIn::create(0.2);
    text->runAction(Sequence::create(DelayTime::create(EXPLAINFRAMEBUTTONSTIME+0.4),appear4, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    
}