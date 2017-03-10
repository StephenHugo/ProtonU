#include "Ch1SceneInside.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch1Scene.h"
#include "Ch2Scene.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch1Inside::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch1Inside::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch1Inside::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    UserDefault * def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 1);
    auto language = def->getStringForKey("LANGUAGE", "english");
    def->flush();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile("scripts/masterscript.txt");
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str());
    script = Json_getItem(chapterScript, "chapter 1");
    
    //// background
    
    auto lobbyImage = Sprite::create(LOBBYIMAGE);
    
    lobbyImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    lobbyImage->setScale( visibleSize.width/lobbyImage->getContentSize().width, visibleSize.height/lobbyImage->getContentSize().height );
    
    this->addChild(lobbyImage,-2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH1);

        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH1, true);
        
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNav( this );
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIOGOINSIDE);
    
    //// preload the audio
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIOTHISISTHELOBBY);
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch1Inside::jeffersonAppears), lagTime);
    
    lagTime += CH1AUDIOTIMETHISISTHELOBBY + 1.2;
    
    this->scheduleOnce(schedule_selector(Ch1Inside::childLifeSpecialistAppears), lagTime);
    
    this->scheduleOnce(schedule_selector(Ch1Inside::radiationText), lagTime + CH1AUDIOTIMECHILDLIFEHI+0.6);
    
    this->scheduleOnce(schedule_selector(Ch1Inside::finishChapterButtonsAppear), lagTime + CH1AUDIOTIMECHILDLIFEHI + CH1AUDIOTIMERADIATIONMEDICINE+1.2);
    
    return true;
}

void Ch1Inside::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    UserDefault * def = UserDefault::getInstance();
    def->setBoolForKey("RETURNVISIT", true);
    def->flush();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch2Scene = Ch2::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, ch2Scene));
}

void Ch1Inside::gotoChapter2Callback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    UserDefault * def = UserDefault::getInstance();
    def->setBoolForKey("RETURNVISIT", true);
    def->flush();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch2Scene = Ch2::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch2Scene));
    
}

void Ch1Inside::repeatChapter1Callback(Ref* pSender)
{
    this->unscheduleAllCallbacks();

    UserDefault * def = UserDefault::getInstance();
    def->setBoolForKey("RETURNVISIT", true);
    def->flush();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch1Scene = Ch1::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch1Scene));
    
}

void Ch1Inside::jeffersonAppears(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOTHISISTHELOBBY);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH1AUDIOTIMETHISISTHELOBBY), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "1.7", "Go Gators!");
    
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
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(CH1AUDIOTIMETHISISTHELOBBY), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(CH1AUDIOTIMETHISISTHELOBBY), FadeOut::create(0.2), nullptr));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIOCHILDLIFEHI);
}

void Ch1Inside::childLifeSpecialistAppears(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIOTHISISTHELOBBY);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOCHILDLIFEHI);
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    childLife->setScale( 0.25*visibleSize.width/childLife->getContentSize().width, 0.6*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH1AUDIOTIMECHILDLIFEHI+CH1AUDIOTIMERADIATIONMEDICINE+1), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "1.8", "Go Gators!");
    
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
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(CH1AUDIOTIMECHILDLIFEHI+1), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(CH1AUDIOTIMECHILDLIFEHI), FadeOut::create(0.2), nullptr));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIORADIATIONMEDICINE);
}

void Ch1Inside::radiationText(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIOCHILDLIFEHI);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIORADIATIONMEDICINE);
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "1.9.1", "Go Gators!");
    auto textString2 = Json_getString(script, "1.9.2", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    text->setColor(cocos2d::Color3B::BLACK);
    text->setOpacity(0);
    
    auto text2 = Label::createWithTTF(textString2, FELTFONT, visibleSize.height*TEXTSIZE);
    text2->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*2.15/20 + origin.y));
    text2->setWidth(0.6*visibleSize.width);
    text2->setHeight(visibleSize.height*3.2/20);
    text2->setColor(cocos2d::Color3B::BLACK);
    text2->setOpacity(0);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*1.85/20 + origin.y));
    textBox->setScale( 0.65*visibleSize.width/textBox->getContentSize().width, 0.25*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    this->addChild(text2,43);
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(CH1AUDIOTIMERADIATIONMEDICINE), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(7.8*TEMPO), FadeOut::create(0.2), nullptr));
    auto appear3 = FadeIn::create(0.2);
    text2->runAction(Sequence::create(DelayTime::create(8.2*TEMPO),appear3, DelayTime::create(CH1AUDIOTIMERADIATIONMEDICINE-8.2*TEMPO), FadeOut::create(0.2), nullptr));
    
}

void Ch1Inside::finishChapterButtonsAppear(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIORADIATIONMEDICINE);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    //// Create finish chapter/go back buttons for the frame
    
    auto gotoChapter2 = MenuItemImage::create(
                                              NAVRIGHTON,
                                              NAVRIGHTOFF,
                                              CC_CALLBACK_1(Ch1Inside::gotoChapter2Callback, this));
    
    gotoChapter2->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height/2 + origin.y));
    gotoChapter2->setScale( 0.1*visibleSize.width/gotoChapter2->getContentSize().width, 0.2*visibleSize.width/gotoChapter2->getContentSize().height );
    
    auto repeatChapter1 = MenuItemImage::create(
                                              NAVLEFTON,
                                              NAVLEFTOFF,
                                              CC_CALLBACK_1(Ch1Inside::repeatChapter1Callback, this));
    
    repeatChapter1->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height/2 + origin.y));
    repeatChapter1->setScale( 0.1*visibleSize.width/repeatChapter1->getContentSize().width, 0.2*visibleSize.width/repeatChapter1->getContentSize().height );
    
    
    // create menu, it's an autorelease object
    auto frameButtons = Menu::create(gotoChapter2, repeatChapter1, NULL);
    frameButtons->setPosition(Vec2::ZERO);
    frameButtons->setOpacity(0);
    
    this->addChild(frameButtons, 1);
    
    auto appear = FadeIn::create(0.2);
    frameButtons->runAction(appear);
    
    this->scheduleOnce(schedule_selector(Ch1Inside::explanationsAppear), 0.2);
    
    this->scheduleOnce(schedule_selector(Ch1Inside::gotonextScene), 2*LAUNCHTRANSITIONTIME);
    
}

void Ch1Inside::explanationsAppear(float dt)
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