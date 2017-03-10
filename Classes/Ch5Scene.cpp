#include "Ch5Scene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch5SceneGrad.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

#include <cmath>
#include <cstdlib>

USING_NS_CC;

Scene* Ch5::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch5::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch5::init()
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
    
    auto chimesImage = Sprite::create(CHIMESIMAGE);
    
    chimesImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    chimesImage->setScale( visibleSize.width/chimesImage->getContentSize().width, visibleSize.height/chimesImage->getContentSize().height );
    
    this->addChild(chimesImage, -2);
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICALMAMATER);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICALMAMATER, true);
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNav( this );
    
    //// tell the story
    
    auto lagTime = 0.5*LAUNCHTRANSITIONTIME;
    
    this->scheduleOnce(schedule_selector(Ch5::jeffersonAppears), lagTime);
    
    lagTime += CH5AUDIOTIMELASTDAY + 0.4;
    
    this->scheduleOnce(schedule_selector(Ch5::ringChimes), lagTime);
    
    return true;
}

void Ch5::gotonextScene(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH5AUDIOCHIMES);
    this->unscheduleAllCallbacks();
    auto gradScene = Ch5Grad::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, gradScene));
}

void Ch5::jeffersonAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH5AUDIOLASTDAY);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH5AUDIOLASTDAY);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH5AUDIOTIMELASTDAY + 1), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "5.1", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH5AUDIOTIMELASTDAY + 1), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH5AUDIOTIMELASTDAY), FadeOut::create(0.2), nullptr));
    
    //// construct the chimes
    
    auto c1 = Sprite::create(CHIME1IMAGE);
    auto c2 = Sprite::create(CHIME2IMAGE);
    auto c3 = Sprite::create(CHIME3IMAGE);
    auto c4 = Sprite::create(CHIME4IMAGE);
    auto c5 = Sprite::create(CHIME5IMAGE);
    auto c6 = Sprite::create(CHIME6IMAGE);
    auto cCenter = Sprite::create(CHIMECENTERIMAGE);
    auto cRope = Sprite::create(CHIMEROPEIMAGE);
    
    cRope->setAnchorPoint(Vec2(0.5, 0));
    
    std::vector<Sprite*> _chimes;
    _chimes.push_back(c1);
    _chimes.push_back(c2);
    _chimes.push_back(c3);
    _chimes.push_back(c4);
    _chimes.push_back(c5);
    _chimes.push_back(c6);
    _chimes.push_back(cCenter);
    _chimes.push_back(cRope);
    
    float yadjust = 0.08f;
    this->setPosNScale(c1, 0.57, 0.65 + yadjust, 0.05, 0.28);
    this->setPosNScale(c2, 0.43, 0.65 + yadjust, 0.05, 0.25);
    this->setPosNScale(c3, 0.5, 0.77 + yadjust, 0.05, 0.17);
    
    this->setPosNScale(cCenter, 0.5, 0.62 + yadjust, 0.05, 0.25);
    this->setPosNScale(cRope, 0.505, 0.14 + yadjust, 0.05, 0.2);
    
    this->setPosNScale(c4, 0.45, 0.55 + yadjust, 0.05, 0.3);
    this->setPosNScale(c5, 0.40, 0.65 + yadjust, 0.05, 0.26);
    this->setPosNScale(c6, 0.55, 0.62 + yadjust, 0.06, 0.23);
    
    std::vector<float> xPos = {0.57, 0.43, 0.5, 0.45, 0.40, 0.55};
    std::vector<float> yPos = {0.65, 0.65, 0.77, 0.55, 0.65, 0.62};

    //// set up the rope listener
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH5AUDIOCHIMES);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto x = touch->getLocation().x/visibleSize.width;
        auto y = touch->getLocation().y/visibleSize.height;
        if (x < 0.6 && x > 0.4 && y < 0.38+yadjust && y > 0.12+yadjust) {
            return true;
        }
        return false;
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        //// move the object around
        auto pos = touch->getLocation();
        
        _chimes[6]->setPosition(Vec2(clampf(pos.x/2 + visibleSize.width/4, 0.46*visibleSize.width, 0.54*visibleSize.width) ,(0.62+yadjust)*visibleSize.height + origin.y));
        _chimes[7]->setPosition(Vec2(clampf(pos.x, 0.405*visibleSize.width, 0.605*visibleSize.width) ,(0.14+yadjust)*visibleSize.height + origin.y));
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        std::vector<int> sign = {1, -1, 1, -1, 1, -1};
        for (int i = 0; i<6; i++) {
            _chimes[i]->stopAllActions();
            _chimes[i]->runAction(MoveTo::create(0.3, Vec2(xPos[i]*visibleSize.width, (yPos[i]+yadjust)*visibleSize.height + origin.y)));
            float r = (std::rand() % 75) / 100.0f + 0.25;
            _chimes[i]->runAction(Repeat::create(Sequence::create(MoveBy::create(0.4, Vec2(r*sign[i]*0.05*visibleSize.width/2, 0)), DelayTime::create(0.1), MoveBy::create(0.8, Vec2(r*sign[i]*-0.05*visibleSize.width, 0)), DelayTime::create(0.1), MoveBy::create(0.4, Vec2(r*sign[i]*0.05*visibleSize.width/2, 0)), nullptr), 5));
            _chimes[i]->runAction(Repeat::create(Sequence::create(RotateTo::create(0.2, r*4), DelayTime::create(0.05), RotateTo::create(0.4, r*-8), DelayTime::create(0.05), RotateTo::create(0.2, 0), nullptr), 11));
        }
        _chimes[6]->runAction(EaseBackOut::create(MoveTo::create(0.9, Vec2(0.5*visibleSize.width, (0.62+yadjust)*visibleSize.height + origin.y))));
        _chimes[7]->runAction(EaseBackOut::create(MoveTo::create(1, Vec2(0.505*visibleSize.width, (0.14+yadjust)*visibleSize.height + origin.y))));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH5AUDIOCHIMES);
        
        this->scheduleOnce(schedule_selector(Ch5::gotonextScene), CH5AUDIOTIMELASTDAY + 0.4 + CH5AUDIOTIMEDRAGROPE + LAUNCHTRANSITIONTIME);
        return true;
    };
    
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Ch5::setPosNScale(cocos2d::Sprite *sprite, float xx, float yy, float sxx, float syy)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width*xx + origin.x, visibleSize.height*yy + origin.y));
    
    sprite->setScale( sxx*visibleSize.width/sprite->getContentSize().width, syy*visibleSize.width/sprite->getContentSize().height);
    
    sprite->setOpacity(0);
    
    this->addChild(sprite);
    
    sprite->runAction(Sequence::create(DelayTime::create(0.2), FadeIn::create(0.4), nullptr));
}

void Ch5::ringChimes(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(CH5AUDIOLASTDAY);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH5AUDIODRAGROPE);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH5AUDIODRAGROPE);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
    jefferson->setScale( 0.35*visibleSize.width/jefferson->getContentSize().width, 0.35*visibleSize.width/jefferson->getContentSize().height);
    
    this->addChild(jefferson,-1);
    
    jefferson->setOpacity(0);
    
    jefferson->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(CH5AUDIOTIMEDRAGROPE), FadeOut::create(0.2),nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "5.2", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH5AUDIOTIMEDRAGROPE), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH5AUDIOTIMEDRAGROPE), FadeOut::create(0.2), nullptr));
    
}
