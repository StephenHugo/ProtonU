#include "Ch4Scene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch4SceneDrag.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

USING_NS_CC;

Scene* Ch4::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch4::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch4::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    UserDefault * def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 4);
    auto language = def->getStringForKey("LANGUAGE", "english");
    def->flush();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile("scripts/masterscript.txt");
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str());
    script = Json_getItem(chapterScript, "chapter 4");
    
    //// background
    
    auto gantryImage = Sprite::create(GANTRYIMAGE);
    
    gantryImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    gantryImage->setScale( visibleSize.width/gantryImage->getContentSize().width, visibleSize.height/gantryImage->getContentSize().height );
    
    this->addChild(gantryImage, -2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH4);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH4, true);
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNav( this );
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch4::jeffersonAppears), lagTime);
    
    lagTime += CH4AUDIOTIMETREATMENTHAPPENS + 0.4;

    this->scheduleOnce(schedule_selector(Ch4::childLifeSpecialistAppears), lagTime);
    
    lagTime += CH4AUDIOTIMELETSLEARN + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::explainSnout), lagTime);
    
    lagTime += CH4AUDIOTIMESNOUT + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::explainTable), lagTime);
    
    lagTime += CH4AUDIOTIMETABLE + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::explainXrayPanels), lagTime);
    
    lagTime += CH4AUDIOTIMEXRAY + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::explainCameras), lagTime);
    
    lagTime += CH4AUDIOTIMECAMERAS + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::explainSoundSystem), lagTime);
    
    lagTime += CH4AUDIOTIMESOUND + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::jeffersonReappears), lagTime);
    
    lagTime += CH4AUDIOTIMESINGDANCE + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4::childLifeSpecialistReappears), lagTime);
    
    lagTime += CH4AUDIOTIMEBEQUIET + 0.4;

    this->scheduleOnce(schedule_selector(Ch4::gotonextScene), lagTime);
    
    return true;
}

void Ch4::gotonextScene(float dt)
{
    
    auto dragScene = Ch4Drag::createScene();
    
    Director::getInstance()->pushScene(TransitionCrossFade::create(0.2, dragScene));
}

void Ch4::jeffersonAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOTREATMENTHAPPENS);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOTREATMENTHAPPENS);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMETREATMENTHAPPENS), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.1", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMETREATMENTHAPPENS), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMETREATMENTHAPPENS), FadeOut::create(0.2), nullptr));
    
}

void Ch4::childLifeSpecialistAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOTREATMENTHAPPENS);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOLETSLEARN);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOLETSLEARN);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*1/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMELETSLEARN), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.2", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMELETSLEARN+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMELETSLEARN), FadeOut::create(0.2), nullptr));
    
}

void Ch4::explainSnout(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOLETSLEARN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOSNOUT);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOSNOUT);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// point at object
    
    auto greenArrow = Sprite::create(ARROWIMAGE);
    
    greenArrow->setPosition(Vec2(visibleSize.width*0.6 + origin.x,visibleSize.height*0.7 + origin.y));
    greenArrow->setScale( 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height);
    
    this->addChild(greenArrow,-1);
    
    greenArrow->setOpacity(0);
    
    auto pointy = Sequence::create(ScaleTo::create(0.3, 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height), ScaleTo::create(0.6, 0.12*visibleSize.width/greenArrow->getContentSize().width, 0.12*visibleSize.height/greenArrow->getContentSize().height), nullptr);
    greenArrow->runAction(RepeatForever::create(pointy));
    greenArrow->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMESNOUT), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.3", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMESNOUT+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMESNOUT), FadeOut::create(0.2), nullptr));
    
}

void Ch4::explainTable(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOSNOUT);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOTABLE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOTABLE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// point at object
    
    auto greenArrow = Sprite::create(ARROWIMAGE);
    
    greenArrow->setPosition(Vec2(visibleSize.width*0.63 + origin.x,visibleSize.height*0.5 + origin.y));
    greenArrow->setScale( 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height);
    
    this->addChild(greenArrow,-1);
    
    greenArrow->setOpacity(0);
    
    auto pointy = Sequence::create(ScaleTo::create(0.3, 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height), ScaleTo::create(0.6, 0.12*visibleSize.width/greenArrow->getContentSize().width, 0.12*visibleSize.height/greenArrow->getContentSize().height), nullptr);
    greenArrow->runAction(RepeatForever::create(pointy));
    greenArrow->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMETABLE), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.4", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMETABLE+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMETABLE), FadeOut::create(0.2), nullptr));
    
}

void Ch4::explainXrayPanels(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOTABLE);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOXRAY);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOXRAY);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// point at object
    
    auto greenArrow = Sprite::create(ARROWIMAGE);
    
    greenArrow->setPosition(Vec2(visibleSize.width*0.48 + origin.x,visibleSize.height*0.56 + origin.y));
    greenArrow->setScale( 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height);
    
    this->addChild(greenArrow,-1);
    
    greenArrow->setOpacity(0);
    
    auto pointy = Sequence::create(ScaleTo::create(0.3, 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height), ScaleTo::create(0.6, 0.12*visibleSize.width/greenArrow->getContentSize().width, 0.12*visibleSize.height/greenArrow->getContentSize().height), nullptr);
    greenArrow->runAction(RepeatForever::create(pointy));
    greenArrow->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMEXRAY), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.5", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMEXRAY+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMEXRAY), FadeOut::create(0.2), nullptr));
    
}

void Ch4::explainCameras(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOXRAY);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOCAMERAS);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOCAMERAS);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// point at objects
    
    auto greenArrow = Sprite::create(ARROWIMAGE);
    
    greenArrow->setPosition(Vec2(visibleSize.width*0.84 + origin.x,visibleSize.height*0.68 + origin.y));
    greenArrow->setScale( 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height);
    
    this->addChild(greenArrow,-1);
    
    greenArrow->setOpacity(0);
    
    auto pointy = Sequence::create(ScaleTo::create(0.3, 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height), ScaleTo::create(0.6, 0.12*visibleSize.width/greenArrow->getContentSize().width, 0.12*visibleSize.height/greenArrow->getContentSize().height), nullptr);
    greenArrow->runAction(RepeatForever::create(pointy));
    greenArrow->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMECAMERAS), FadeOut::create(0.2),nullptr));
    
    auto greenArrow2 = Sprite::create(ARROWIMAGE);
    
    greenArrow2->setPosition(Vec2(visibleSize.width*0.22 + origin.x,visibleSize.height*0.72 + origin.y));
    greenArrow2->setScale( 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height);
    
    this->addChild(greenArrow2,-1);
    
    greenArrow2->setFlippedX(true);
    
    greenArrow2->setOpacity(0);
    
    auto pointy2 = Sequence::create(ScaleTo::create(0.3, 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height), ScaleTo::create(0.6, 0.12*visibleSize.width/greenArrow->getContentSize().width, 0.12*visibleSize.height/greenArrow->getContentSize().height), nullptr);
    greenArrow2->runAction(RepeatForever::create(pointy2));
    greenArrow2->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMECAMERAS), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.6", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMECAMERAS+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMECAMERAS), FadeOut::create(0.2), nullptr));
    
}

void Ch4::explainSoundSystem(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOCAMERAS);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOSOUND);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOSOUND);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.7", "Go Gators!");
    
    //// point at object
    
    auto greenArrow = Sprite::create(ARROWIMAGE);
    
    greenArrow->setPosition(Vec2(visibleSize.width*0.3 + origin.x,visibleSize.height*0.33 + origin.y));
    greenArrow->setScale( 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height);
    
    this->addChild(greenArrow,-1);
    
    greenArrow->setOpacity(0);
    
    auto pointy = Sequence::create(ScaleTo::create(0.3, 0.1*visibleSize.width/greenArrow->getContentSize().width, 0.1*visibleSize.height/greenArrow->getContentSize().height), ScaleTo::create(0.6, 0.12*visibleSize.width/greenArrow->getContentSize().width, 0.12*visibleSize.height/greenArrow->getContentSize().height), nullptr);
    greenArrow->runAction(RepeatForever::create(pointy));
    greenArrow->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMESOUND), FadeOut::create(0.2),nullptr));
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMESOUND), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMESOUND), FadeOut::create(0.2), nullptr));
    
}

void Ch4::jeffersonReappears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOSOUND);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOSINGDANCE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOSINGDANCE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMESINGDANCE+CH4AUDIOTIMEBEQUIET+0.4*TEMPO), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.8", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMESINGDANCE+1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMESINGDANCE), FadeOut::create(0.2), nullptr));
    
}

void Ch4::childLifeSpecialistReappears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH4AUDIOSINGDANCE);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIOBEQUIET);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIOBEQUIET);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto childLife = Sprite::create(CHILDLIFESPECIALISTIMAGE);
    
    childLife->setPosition(Vec2(visibleSize.width*1/3 + origin.x,visibleSize.height*2/5 + origin.y));
    childLife->setScale( 0.3*visibleSize.width/childLife->getContentSize().width, 0.75*visibleSize.height/childLife->getContentSize().height);
    
    this->addChild(childLife,-1);
    
    childLife->setOpacity(0);
    
    childLife->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH4AUDIOTIMEBEQUIET), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.9", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMEBEQUIET), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMEBEQUIET), FadeOut::create(0.2), nullptr));
    
}
