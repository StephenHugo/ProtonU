#include "Ch3SceneCalendar.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch3Scene.h"
#include "Ch4Scene.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch3Calendar::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch3Calendar::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch3Calendar::init()
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
    
    auto cloudsImage = Sprite::create(CALENDARBACKGROUNDIMAGE);
    
    cloudsImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    cloudsImage->setScale( visibleSize.width/cloudsImage->getContentSize().width, visibleSize.height/cloudsImage->getContentSize().height );
    
    this->addChild(cloudsImage,-2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH3);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH3, true);
    }
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarAppears), lagTime);
    
    return true;
}

void Ch3Calendar::gotoChapter4Callback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch4Scene = Ch4::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch4Scene));
    
}

void Ch3Calendar::repeatChapter3Callback(Ref* pSender)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch3Scene = Ch3::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch3Scene));
    
}

void Ch3Calendar::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto nextScene = Ch4::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(2, nextScene));
}

void Ch3Calendar::calendarAppears(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.16.1", "Go Gators!");
    auto textString2 = Json_getString(script, "3.16.2", "Go Gators!");
    auto textString3 = Json_getString(script, "3.16.3", "Go Gators!");
    
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
    
    auto text3 = Label::createWithTTF(textString3, FELTFONT, visibleSize.height*TEXTSIZE);
    text3->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text3->setWidth(0.6*visibleSize.width);
    text3->setHeight(visibleSize.height*3.2/20);
    text3->setColor(cocos2d::Color3B::BLACK);
    text3->setOpacity(0);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*1.85/20 + origin.y));
    textBox->setScale( 0.65*visibleSize.width/textBox->getContentSize().width, 0.25*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    this->addChild(text2,43);
    this->addChild(text3,43);
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEAFTERCT), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(4*TEMPO), FadeOut::create(0.2), nullptr));
    text2->runAction(Sequence::create(DelayTime::create(4.4*TEMPO), FadeIn::create(0.2), DelayTime::create(7.5*TEMPO), FadeOut::create(0.2), nullptr));
    text3->runAction(Sequence::create(DelayTime::create(12.3*TEMPO), FadeIn::create(0.2), DelayTime::create(CH3AUDIOTIMEAFTERCT-12.3*TEMPO), FadeOut::create(0.2), nullptr));
    
    calendarPages.push_back(CALENDARPROTONUIMAGE);
    
    calendarPages.push_back(CALENDARZOOIMAGE);
    calendarPages.push_back(CALENDARFISHIMAGE);
    calendarPages.push_back(CALENDARSOCCERIMAGE);
    
    calendarPages.push_back(CALENDARFISHINGIMAGE);
    calendarPages.push_back(CALENDARARTIMAGE);
    calendarPages.push_back(CALENDARSPACEIMAGE);
    calendarPages.push_back(CALENDARBEACHIMAGE);
    
    calendarPages.push_back(CALENDARFOOTBALLIMAGE);
    calendarPages.push_back(CALENDARFLASKIMAGE);
    calendarPages.push_back(CALENDARCARIMAGE);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH3AUDIOAFTERCT);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH3AUDIOAFTERCT);
    
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage1), 0.1);
    
}

void Ch3Calendar::calendarPage1(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 11);
    sprite->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(1.6), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage2), 1.8);
}

void Ch3Calendar::calendarPage2(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 10);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage3), 1.8);
}

void Ch3Calendar::calendarPage3(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 9);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage4), 1.8);
}

void Ch3Calendar::calendarPage4(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 8);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage5), 1.8);
}

void Ch3Calendar::calendarPage5(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 7);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage6), 1.8);
}

void Ch3Calendar::calendarPage6(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 6);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage7), 1.8);
}

void Ch3Calendar::calendarPage7(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 5);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage8), 1.8);
}

void Ch3Calendar::calendarPage8(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 4);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage9), 1.8);
}

void Ch3Calendar::calendarPage9(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 3);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage10), 1.8);
}

void Ch3Calendar::calendarPage10(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 2);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::calendarPage11), 1.8);
}

void Ch3Calendar::calendarPage11(float dt)
{
    
    auto sprite = Sprite::create(calendarPages[currentPage]);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height*3/5 + origin.y));
    sprite->setScale( 0.4*visibleSize.width/sprite->getContentSize().width, 0.4*visibleSize.width/sprite->getContentSize().height);
    
    this->addChild(sprite, 1);
    sprite->runAction(Sequence::create(DelayTime::create(1.8), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    currentPage++;
    this->scheduleOnce(schedule_selector(Ch3Calendar::finishChapterButtonsAppear), 1.8);
}

void Ch3Calendar::finishChapterButtonsAppear(float dt)
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
                                              CC_CALLBACK_1(Ch3Calendar::gotoChapter4Callback, this));
    
    gotoChapter3->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height/2 + origin.y));
    gotoChapter3->setScale( 0.1*visibleSize.width/gotoChapter3->getContentSize().width, 0.2*visibleSize.width/gotoChapter3->getContentSize().height );
    
    auto repeatChapter2 = MenuItemImage::create(
                                                NAVLEFTON,
                                                NAVLEFTOFF,
                                                CC_CALLBACK_1(Ch3Calendar::repeatChapter3Callback, this));
    
    repeatChapter2->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height/2 + origin.y));
    repeatChapter2->setScale( 0.1*visibleSize.width/repeatChapter2->getContentSize().width, 0.2*visibleSize.width/repeatChapter2->getContentSize().height );
    
    
    // create menu, it's an autorelease object
    auto frameButtons = Menu::create(gotoChapter3, repeatChapter2, NULL);
    frameButtons->setPosition(Vec2::ZERO);
    frameButtons->setOpacity(0);
    
    this->addChild(frameButtons, 1);
    
    auto appear = FadeIn::create(0.2);
    frameButtons->runAction(appear);
    
    this->scheduleOnce(schedule_selector(Ch3Calendar::explanationsAppear), 0.2);
    
    this->scheduleOnce(schedule_selector(Ch3Calendar::gotonextScene), 2*LAUNCHTRANSITIONTIME);
    
}

void Ch3Calendar::explanationsAppear(float dt)
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