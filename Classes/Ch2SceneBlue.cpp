#include "Ch2SceneBlue.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch2Scene.h"
#include "ch3Scene.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch2Blue::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch2Blue::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch2Blue::init()
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
    
    auto lagTime = 0.4;
    
    this->scheduleOnce(schedule_selector(Ch2Blue::childLifeSpecialistAppears), lagTime);
    
    lagTime = 0.2 + CH2AUDIOTIMEMEETRADTHERAPIST + 0.8;
    
    this->scheduleOnce(schedule_selector(Ch2Blue::blueDoor), lagTime);

    return true;
}

void Ch2Blue::gotoChapter3Callback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch3Scene = Ch3::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch3Scene));
    
}

void Ch2Blue::repeatChapter2Callback(Ref* pSender)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch2Scene = Ch2::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch2Scene));
    
}

void Ch2Blue::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto ch3Scene = Ch3::createScene();
    
    Director::getInstance()->pushScene(TransitionCrossFade::create(0.4, ch3Scene));
}

void Ch2Blue::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIOMEETNURSEDOCTOR);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIOMEETNURSEDOCTOR);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*1/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMEMEETNURSEDOCTOR), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.7", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEMEETNURSEDOCTOR), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEMEETNURSEDOCTOR), FadeOut::create(0.2), nullptr));
    
    auto blueClosed = Sprite::create(BLUEDOORCLOSED);
    
    blueClosed->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    blueClosed->setScale( visibleSize.width/blueClosed->getContentSize().width, visibleSize.height/blueClosed->getContentSize().height );
    
    this->addChild(blueClosed, -2);
    
    blueClosed->setOpacity(0);
    blueClosed->runAction(Sequence::create(DelayTime::create(CH2AUDIOTIMEMEETNURSEDOCTOR+0.4), FadeIn::create(0.2), nullptr));
    
}

void Ch2Blue::blueDoor(float dt)
{
    
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIOMEETNURSEDOCTOR);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(KNOCKSOUND);
    
    knocked = 0;
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Ch2Blue::onTouchBegan, this, listener);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool Ch2Blue::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::EventListenerTouchOneByOne *listener)
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
        
        auto blueOpened = Sprite::create(BLUEDOOROPEN);
        
        blueOpened->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        blueOpened->setScale( visibleSize.width/blueOpened->getContentSize().width, visibleSize.height/blueOpened->getContentSize().height );
        
        this->addChild(blueOpened, -2);
        
        blueOpened->setOpacity(0);
        blueOpened->runAction(Sequence::create(DelayTime::create(LAUNCHTRANSITIONTIME*0.2),FadeIn::create(0.2), nullptr));
        this->scheduleOnce(schedule_selector(Ch2Blue::blueDoorOpens), LAUNCHTRANSITIONTIME*0.25);
    }
    
    return true;
}

void Ch2Blue::blueDoorOpens(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(KNOCKSOUND);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIORESTOFTEAM);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIORESTOFTEAM);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMERESTOFTEAM), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.8", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMERESTOFTEAM), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMERESTOFTEAM), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch2Blue::doctorAppears), CH2AUDIOTIMERESTOFTEAM+0.8);
}

void Ch2Blue::doctorAppears(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIODOCTOR);
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIORESTOFTEAM);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIODOCTOR);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto examRoom = Sprite::create(EXAMROOMIMAGE);
    
    examRoom->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    examRoom->setScale( visibleSize.width/examRoom->getContentSize().width, visibleSize.height/examRoom->getContentSize().height );
    
    this->addChild(examRoom, -2);
    
    examRoom->setOpacity(0);
    examRoom->runAction(FadeIn::create(0.2));
    
    ////
    
    auto radDoctor = Sprite::create(DOCIMAGE);
    
    radDoctor->setPosition(Vec2(visibleSize.width*1.5/5 + origin.x,visibleSize.height*2/5 + origin.y));
    radDoctor->setScale( 0.3*visibleSize.width/radDoctor->getContentSize().width, 0.75*visibleSize.height/radDoctor->getContentSize().height);
    
    this->addChild(radDoctor,-1);
    
    radDoctor->setOpacity(0);
    
    radDoctor->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMEDOCTOR+CH2AUDIOTIMENURSE+0.4), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.10.1", "Go Gators!");
    auto textString2 = Json_getString(script, "2.10.2", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEDOCTOR), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(7.2*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(7.6*TEMPO),FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMEDOCTOR-7.6*TEMPO), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch2Blue::andNurse), CH2AUDIOTIMEDOCTOR+0.4);
}

void Ch2Blue::andNurse(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIODOCTOR);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH2AUDIONURSE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH2AUDIONURSE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto nurse = Sprite::create(NURSE2IMAGE);
    
    nurse->setPosition(Vec2(visibleSize.width*3.5/5 + origin.x,visibleSize.height*2/5 + origin.y));
    nurse->setScale( 0.4*visibleSize.width/nurse->getContentSize().width, 0.75*visibleSize.height/nurse->getContentSize().height);
    
    this->addChild(nurse,-1);
    
    nurse->setOpacity(0);
    
    nurse->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH2AUDIOTIMENURSE), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.9", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMENURSE), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH2AUDIOTIMENURSE), FadeOut::create(0.2), nullptr));
    
    this->scheduleOnce(schedule_selector(Ch2Blue::finishChapterButtonsAppear), CH2AUDIOTIMENURSE+0.8);
}

void Ch2Blue::finishChapterButtonsAppear(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH2AUDIONURSE);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    //// Create finish chapter/go back buttons for the frame
    
    auto gotoChapter3 = MenuItemImage::create(
                                              NAVRIGHTON,
                                              NAVRIGHTOFF,
                                              CC_CALLBACK_1(Ch2Blue::gotoChapter3Callback, this));
    
    gotoChapter3->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height/2 + origin.y));
    gotoChapter3->setScale( 0.1*visibleSize.width/gotoChapter3->getContentSize().width, 0.2*visibleSize.width/gotoChapter3->getContentSize().height );
    
    auto repeatChapter2 = MenuItemImage::create(
                                                NAVLEFTON,
                                                NAVLEFTOFF,
                                                CC_CALLBACK_1(Ch2Blue::repeatChapter2Callback, this));
    
    repeatChapter2->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height/2 + origin.y));
    repeatChapter2->setScale( 0.1*visibleSize.width/repeatChapter2->getContentSize().width, 0.2*visibleSize.width/repeatChapter2->getContentSize().height );
    
    
    // create menu, it's an autorelease object
    auto frameButtons = Menu::create(gotoChapter3, repeatChapter2, NULL);
    frameButtons->setPosition(Vec2::ZERO);
    frameButtons->setOpacity(0);
    
    this->addChild(frameButtons, 1);
    
    auto appear = FadeIn::create(0.2);
    frameButtons->runAction(appear);
    
    this->scheduleOnce(schedule_selector(Ch2Blue::explanationsAppear), 0.2);
    
    this->scheduleOnce(schedule_selector(Ch2Blue::gotonextScene), 2*LAUNCHTRANSITIONTIME);
    
}

void Ch2Blue::explanationsAppear(float dt)
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