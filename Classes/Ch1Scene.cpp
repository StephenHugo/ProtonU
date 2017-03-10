#include "Ch1Scene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch1SceneInside.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch1::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch1::init()
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
    
    auto buildingImage = Sprite::create(BUILDINGIMAGE);
    
    buildingImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    buildingImage->setScale( visibleSize.width/buildingImage->getContentSize().width, visibleSize.height/buildingImage->getContentSize().height );
    
    this->addChild(buildingImage,-2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH1);

        this->scheduleOnce(schedule_selector(Ch1::playMusic), 0.2);
    }
    
    //// preload the audio
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIOWEEEEEEEE);
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch1::jeffersonAppears), lagTime);
    
    lagTime = 0.5*LAUNCHTRANSITIONTIME + 0.2 + CH1AUDIOTIMEWEEEEE;
    
    this->scheduleOnce(schedule_selector(Ch1::textAppears), lagTime);
    
    lagTime = 0.5*LAUNCHTRANSITIONTIME + 0.2 + CH1AUDIOTIMEWEEEEE + 0.4 + CH1AUDIOTIMEHI;
    
    this->scheduleOnce(schedule_selector(Ch1::explanationsAppearNW), lagTime + 0.1);
    this->scheduleOnce(schedule_selector(Ch1::explanationsAppearNE), lagTime + 0.2+3.6*TEMPO);
    //this->scheduleOnce(schedule_selector(Ch1::explanationsAppearSW), lagTime + 0.3+2*3.6*TEMPO); // removed gotoStars
    //this->scheduleOnce(schedule_selector(Ch1::explanationsAppearSE), lagTime + 0.4+2*3.6*TEMPO);
    
    lagTime = lagTime + 0.5 + 2*3.6*TEMPO; // new lagTime depends on frame buttons
    
    this->scheduleOnce(schedule_selector(Ch1::jeffersonReappears), lagTime);
    
    this->scheduleOnce(schedule_selector(Ch1::gotonextScene), lagTime + CH1AUDIOTIMEGOINSIDE + 0.7);
    
    return true;
}

void Ch1::playMusic(float dt)
{
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH1, true);
    }
}

void Ch1::gotonextScene(float dt)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch1InsideScene = Ch1Inside::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME*1.25, ch1InsideScene));
}

void Ch1::jeffersonAppears(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOWEEEEEEEE);
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.4 + origin.x, visibleSize.height*0.57 + origin.y));
    jefferson->setScale( 0.05*visibleSize.width/jefferson->getContentSize().width, 0.05*visibleSize.width/jefferson->getContentSize().height );
    
    auto fromLogo = EaseExponentialIn::create(MoveTo::create(CH1AUDIOTIMEWEEEEE, Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y)));
    
    auto growJefferson = ScaleTo::create(CH1AUDIOTIMEWEEEEE, 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height );
    auto spinJefferson = Repeat::create(RotateBy::create(CH1AUDIOTIMEWEEEEE/2, 540), 2);
    this->addChild(jefferson);
    
    jefferson->setOpacity(0);
    jefferson->runAction(Spawn::create(FadeIn::create(0.2),growJefferson,spinJefferson,fromLogo,nullptr));
    
    jefferson->runAction(Sequence::create(DelayTime::create(CH1AUDIOTIMEHI + 0.2 + CH1AUDIOTIMEWEEEEE), FadeOut::create(0.2),nullptr));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIOHI);
}

void Ch1::textAppears(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIOWEEEEEEEE);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOHI);
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNav( this );
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "1.1", "Go Gators!");
    auto textString2 = Json_getString(script, "1.2", "Go Gators!");
    
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
    textBox->runAction(Sequence::create(appear, DelayTime::create(CH1AUDIOTIMEHI), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(CH1AUDIOTIMEHI-4*TEMPO), FadeOut::create(0.2), nullptr));
    auto appear3 = FadeIn::create(0.2);
    text2->runAction(Sequence::create(DelayTime::create(CH1AUDIOTIMEHI-3.8*TEMPO),appear3, DelayTime::create(3.6*TEMPO), FadeOut::create(0.4), nullptr));
    
}

void Ch1::explanationsAppearNW(float dt)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH1AUDIOHI);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textString = Json_getString(script, "menu", "Go Gators!");
    
    //// begin explanations of the NW frame button
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.29 + origin.x, visibleSize.height*0.74 + origin.y));
    text->setWidth(0.40*visibleSize.width);
    text->setHeight(visibleSize.height*0.25);
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(BUBBLENWIMAGE);
    
    textBox->setPosition(Vec2(visibleSize.width*0.27 + origin.x, visibleSize.height*0.8 + origin.y));
    textBox->setScale( 0.45*visibleSize.width/textBox->getContentSize().width, 0.23*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    
}

void Ch1::explanationsAppearNE(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textString = Json_getString(script, "volume", "Go Gators!");
    
    //// begin explanations of the NE frame button
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.73 + origin.x, visibleSize.height*0.74 + origin.y));
    text->setWidth(0.41*visibleSize.width);
    text->setHeight(visibleSize.height*0.25);
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(BUBBLENEIMAGE);
    textBox->setPosition(Vec2(visibleSize.width*0.73 + origin.x, visibleSize.height*0.8 + origin.y));
    textBox->setScale( 0.45*visibleSize.width/textBox->getContentSize().width, 0.23*visibleSize.height/textBox->getContentSize().height );
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    
}

void Ch1::explanationsAppearSW(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textString = Json_getString(script, "stars", "Go Gators!");
    
    //// begin explanations of the SW frame button
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.29 + origin.x, visibleSize.height*0.17 + origin.y));
    text->setWidth(0.41*visibleSize.width);
    text->setHeight(visibleSize.height*0.25);
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(BUBBLESWIMAGE);
    
    textBox->setPosition(Vec2(visibleSize.width*0.27 + origin.x, visibleSize.height*0.2 + origin.y));
    textBox->setScale( 0.45*visibleSize.width/textBox->getContentSize().width, 0.23*visibleSize.height/textBox->getContentSize().height );
    
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    
}

void Ch1::explanationsAppearSE(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textString = Json_getString(script, "notes", "Go Gators!");
    
    //// begin explanations of the SE frame button
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.73 + origin.x, visibleSize.height*0.17 + origin.y));
    text->setWidth(0.41*visibleSize.width);
    text->setHeight(visibleSize.height*0.25);
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    auto textBox = Sprite::create(BUBBLESEIMAGE);
    textBox->setPosition(Vec2(visibleSize.width*0.73 + origin.x, visibleSize.height*0.2 + origin.y));
    textBox->setScale( 0.45*visibleSize.width/textBox->getContentSize().width, 0.23*visibleSize.height/textBox->getContentSize().height );
    textBox->setOpacity(0);
    
    this->addChild(textBox,42);
    
    this->addChild(text,43);
    
    auto appear = FadeIn::create(0.2);
    textBox->runAction(Sequence::create(appear, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), nullptr));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH1AUDIOGOINSIDE);
}

void Ch1::jeffersonReappears(float dt)
{
    
    //// Set the return visit variable to true and open the main menu
    UserDefault * def = UserDefault::getInstance();
    def->setBoolForKey("RETURNVISIT", true);
    def->flush();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH1AUDIOGOINSIDE);
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH1AUDIOTIMEGOINSIDE), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "1.6", "Go Gators!");
    
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
    textBox->runAction(Sequence::create(appear, DelayTime::create(CH1AUDIOTIMEGOINSIDE), FadeOut::create(0.4), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(CH1AUDIOTIMEGOINSIDE), FadeOut::create(0.4), nullptr));

    
}
