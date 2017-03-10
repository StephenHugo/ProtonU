#include "Ch4SceneDrag.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch4Scene.h"
#include "Ch5Scene.h"

#include "FrameStuff.h"
#include <fstream>
#include "spine/json.h"

#include <cmath>

USING_NS_CC;

enum {LCAM, RCAM, TABLE, SNOUT, XRAY, SPEAKER};

Scene* Ch4Drag::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ch4Drag::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Ch4Drag::init()
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
    
    this->addChild(gantryImage, -3);
    
    gantryImage->runAction(EaseInOut::create(MoveTo::create(CH4AUDIOTIMEDRAGITEMS/2, Vec2(visibleSize.width/2 + origin.x, 0.4*visibleSize.height + origin.y)),CH4AUDIOTIMEDRAGITEMS/2));
    
    //// Begin music!
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICCH4);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICCH4, true);
    }
    
    //// add the frame elements to the chapter layer
    
    FrameNav frameNav;
    frameNav.addFrameNavNoDelay( this );
    
    //// tell the story
    
    auto lagTime = 0.4;
    
    this->scheduleOnce(schedule_selector(Ch4Drag::jeffersonAppears), lagTime);
    
    return true;
}

void Ch4Drag::gotoChapter5Callback(Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch5Scene = Ch5::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch5Scene));
    
}

void Ch4Drag::repeatChapter4Callback(Ref* pSender)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    auto ch4Scene = Ch4::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch4Scene));
    
}

void Ch4Drag::gotonextScene(float dt)
{
    this->unscheduleAllCallbacks();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto nextScene = Ch5::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(2, nextScene));
}

void Ch4Drag::jeffersonAppears(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CH4AUDIODRAGITEMS);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH4AUDIODRAGITEMS);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto objectBar = Sprite::create(BARFOROBJECTS);
    
    objectBar->setPosition(Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*0.93 + origin.y));
    objectBar->setScale( visibleSize.width/objectBar->getContentSize().width, 0.12*visibleSize.width/objectBar->getContentSize().height);
    
    this->addChild(objectBar,-2);
    
    objectBar->setOpacity(0);
    
    objectBar->runAction(Spawn::create(FadeIn::create(0.4), EaseInOut::create(MoveTo::create(CH4AUDIOTIMEDRAGITEMS/2, Vec2(visibleSize.width*0.5 + origin.x,visibleSize.height*0.88 + origin.y)), CH4AUDIOTIMEDRAGITEMS/2), nullptr));
    
    //// objects appear
    
    auto leftcameraShadow = Sprite::create(CAMERALEFTGHOSTIMAGE);
    auto rightcameraShadow = Sprite::create(CAMERARIGHTGHOSTIMAGE);
    auto tableShadow = Sprite::create(TABLEGHOSTIMAGE);
    auto snoutShadow = Sprite::create(SNOUTGHOSTIMAGE);
    auto xrayShadow = Sprite::create(XRAYGHOSTIMAGE);
    auto speakerShadow = Sprite::create(SPEAKERGHOSTIMAGE);
    
    leftcameraShadow->setPosition(Vec2(visibleSize.width*1/7 + origin.x, visibleSize.height*0.88 + origin.y));
    rightcameraShadow->setPosition(Vec2(visibleSize.width*2/7 + origin.x, visibleSize.height*0.88 + origin.y));
    tableShadow->setPosition(Vec2(visibleSize.width*3/7 + origin.x, visibleSize.height*0.88 + origin.y));
    snoutShadow->setPosition(Vec2(visibleSize.width*4/7 + origin.x, visibleSize.height*0.88 + origin.y));
    xrayShadow->setPosition(Vec2(visibleSize.width*5/7 + origin.x, visibleSize.height*0.88 + origin.y));
    speakerShadow->setPosition(Vec2(visibleSize.width*6/7 + origin.x, visibleSize.height*0.88 + origin.y));
    
    leftcameraShadow->setScale( 0.1*visibleSize.width/leftcameraShadow->getContentSize().width, 0.1*visibleSize.width/leftcameraShadow->getContentSize().height);
    rightcameraShadow->setScale( 0.1*visibleSize.width/rightcameraShadow->getContentSize().width, 0.1*visibleSize.width/rightcameraShadow->getContentSize().height);
    tableShadow->setScale( 0.1*visibleSize.width/tableShadow->getContentSize().width, 0.1*visibleSize.width/tableShadow->getContentSize().height);
    snoutShadow->setScale( 0.1*visibleSize.width/snoutShadow->getContentSize().width, 0.1*visibleSize.width/snoutShadow->getContentSize().height);
    xrayShadow->setScale( 0.1*visibleSize.width/xrayShadow->getContentSize().width, 0.1*visibleSize.width/xrayShadow->getContentSize().height);
    speakerShadow->setScale( 0.1*visibleSize.width/speakerShadow->getContentSize().width, 0.1*visibleSize.width/speakerShadow->getContentSize().height);
    
    leftcameraShadow->setOpacity(0);
    rightcameraShadow->setOpacity(0);
    tableShadow->setOpacity(0);
    snoutShadow->setOpacity(0);
    xrayShadow->setOpacity(0);
    speakerShadow->setOpacity(0);
    
    this->addChild(leftcameraShadow,-1);
    this->addChild(rightcameraShadow,-1);
    this->addChild(tableShadow,-1);
    this->addChild(snoutShadow,-1);
    this->addChild(xrayShadow,-1);
    this->addChild(speakerShadow,-1);
    
    //// everything appears
    
    leftcameraShadow->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 1*0.1), FadeIn::create(0.2), nullptr));
    rightcameraShadow->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 2*0.1), FadeIn::create(0.2), nullptr));
    tableShadow->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 3*0.1), FadeIn::create(0.2), nullptr));
    snoutShadow->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 4*0.1), FadeIn::create(0.2), nullptr));
    xrayShadow->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 5*0.1), FadeIn::create(0.2), nullptr));
    speakerShadow->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 6*0.1), FadeIn::create(0.2), nullptr));
    
    auto leftcameraObject = Sprite::create(CAMERALEFTIMAGE);
    auto rightcameraObject = Sprite::create(CAMERARIGHTIMAGE);
    auto tableObject = Sprite::create(TABLEIMAGE);
    auto snoutObject = Sprite::create(SNOUTIMAGE);
    auto xrayObject = Sprite::create(XRAYIMAGE);
    auto speakerObject = Sprite::create(SPEAKERIMAGE);
    
    leftcameraObject->setPosition(Vec2(visibleSize.width*1/7 + origin.x, visibleSize.height*0.88 + origin.y));
    rightcameraObject->setPosition(Vec2(visibleSize.width*2/7 + origin.x, visibleSize.height*0.88 + origin.y));
    tableObject->setPosition(Vec2(visibleSize.width*3/7 + origin.x, visibleSize.height*0.88 + origin.y));
    snoutObject->setPosition(Vec2(visibleSize.width*4/7 + origin.x, visibleSize.height*0.88 + origin.y));
    xrayObject->setPosition(Vec2(visibleSize.width*5/7 + origin.x, visibleSize.height*0.88 + origin.y));
    speakerObject->setPosition(Vec2(visibleSize.width*6/7 + origin.x, visibleSize.height*0.88 + origin.y));
    
    leftcameraObject->setScale( 0.1*visibleSize.width/leftcameraObject->getContentSize().width, 0.1*visibleSize.width/leftcameraObject->getContentSize().height);
    rightcameraObject->setScale( 0.1*visibleSize.width/rightcameraObject->getContentSize().width, 0.1*visibleSize.width/rightcameraObject->getContentSize().height);
    tableObject->setScale( 0.1*visibleSize.width/tableObject->getContentSize().width, 0.1*visibleSize.width/tableObject->getContentSize().height);
    snoutObject->setScale( 0.1*visibleSize.width/snoutObject->getContentSize().width, 0.1*visibleSize.width/snoutObject->getContentSize().height);
    xrayObject->setScale( 0.1*visibleSize.width/xrayObject->getContentSize().width, 0.1*visibleSize.width/xrayObject->getContentSize().height);
    speakerObject->setScale( 0.1*visibleSize.width/speakerObject->getContentSize().width, 0.1*visibleSize.width/speakerObject->getContentSize().height);
    
    leftcameraObject->setOpacity(0);
    rightcameraObject->setOpacity(0);
    tableObject->setOpacity(0);
    snoutObject->setOpacity(0);
    xrayObject->setOpacity(0);
    speakerObject->setOpacity(0);
    
    this->addChild(leftcameraObject,-1);
    this->addChild(rightcameraObject,-1);
    this->addChild(tableObject,-1);
    this->addChild(snoutObject,-1);
    this->addChild(xrayObject,-1);
    this->addChild(speakerObject,-1);
    
    //// build an array of objects to manage drag and drop game
    
    std::vector<Sprite*> _objects;
    _objects.push_back(leftcameraObject);
    _objects.push_back(rightcameraObject);
    _objects.push_back(tableObject);
    _objects.push_back(snoutObject);
    _objects.push_back(xrayObject);
    _objects.push_back(speakerObject);
    
    //// everything appears
    
    leftcameraObject->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 1*0.1), FadeIn::create(0.2), nullptr));
    rightcameraObject->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 2*0.1), FadeIn::create(0.2), nullptr));
    tableObject->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 3*0.1), FadeIn::create(0.2), nullptr));
    snoutObject->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 4*0.1), FadeIn::create(0.2), nullptr));
    xrayObject->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 5*0.1), FadeIn::create(0.2), nullptr));
    speakerObject->runAction(Sequence::create(DelayTime::create(CH4AUDIOTIMEDRAGITEMS/4 + 6*0.1), FadeIn::create(0.2), nullptr));
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.10", "Go Gators!");
    
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
    
    textBox->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMEDRAGITEMS), FadeOut::create(0.4), nullptr));
    text->runAction(Sequence::create(FadeIn::create(0.2), DelayTime::create(CH4AUDIOTIMEDRAGITEMS), FadeOut::create(0.2), nullptr));
    
    //// create a listener to drag and drop objects
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto pos = touch->getLocation();
        auto x = (pos.x - origin.x)/visibleSize.width;
        auto y = (pos.y - origin.y)/visibleSize.height;
        auto boxWidth = 0.07f;
        
        //// check if an object was clicked
        if ( y > 0.75 ){
            
            if ( std::abs(x - 1.0f/7) < boxWidth ){
                
                this->obj = LCAM;
                if (objFound[obj]){return false;}
                _objects[this->obj]->runAction(ScaleBy::create(0.4, 1.2, 1.2));
                _objects[this->obj]->setLocalZOrder(0);
                return true;
                
            } else if ( std::abs(x - 2.0f/7) < boxWidth ){

                this->obj = RCAM;
                if (objFound[obj]){return false;}
                _objects[this->obj]->runAction(ScaleBy::create(0.4, 1.2, 1.2));
                _objects[this->obj]->setLocalZOrder(0);
                return true;
                
            } else if ( std::abs(x - 3.0f/7) < boxWidth ){

                this->obj = TABLE;
                if (objFound[obj]){return false;}
                _objects[this->obj]->runAction(ScaleBy::create(0.4, 1.2, 1.2));
                _objects[this->obj]->setLocalZOrder(0);
                return true;
                
            } else if ( std::abs(x - 4.0f/7) < boxWidth ){

                this->obj = SNOUT;
                if (objFound[obj]){return false;}
                _objects[this->obj]->runAction(ScaleBy::create(0.4, 1.2, 1.2));
                _objects[this->obj]->setLocalZOrder(0);
                return true;
                
            } else if ( std::abs(x - 5.0f/7) < boxWidth ){

                this->obj = XRAY;
                if (objFound[obj]){return false;}
                _objects[this->obj]->runAction(ScaleBy::create(0.4, 1.2, 1.2));
                _objects[this->obj]->setLocalZOrder(0);
                return true;
                
            } else if ( std::abs(x - 6.0f/7) < boxWidth ){

                this->obj = SPEAKER;
                if (objFound[obj]){return false;}
                _objects[this->obj]->runAction(ScaleBy::create(0.4, 1.2, 1.2));
                _objects[this->obj]->setLocalZOrder(0);
                return true;
                
            } else {
                
                return false;
                
            }
        }
        
        //// otherwise, click again
        
        return false;
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        //// move the object around
        auto pos = touch->getLocation();
        
        _objects[this->obj]->setPosition(pos);
        
        return true;
    };

    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto pos = touch->getLocation();
        auto siz = _objects[this->obj]->getContentSize();
        
        Vec2 objLoc = Vec2(-1, -1);
        switch (obj) {
            case LCAM:
                objLoc = Vec2(0.15, 0.65);
                break;
            case RCAM:
                objLoc = Vec2(0.92, 0.62);
                break;
            case TABLE:
                objLoc = Vec2(0.69, 0.42);
                break;
            case SNOUT:
                objLoc = Vec2(0.66, 0.62);
                break;
            case XRAY:
                objLoc = Vec2(0.55, 0.48);
                break;
            case SPEAKER:
                objLoc = Vec2(0.36, 0.27);
                break;
            default:
                break;
        }
        
        _objects[this->obj]->setLocalZOrder(-1);
        
        //// check to see if the object is in the right place
        if (std::abs(objLoc.x-(pos.x-origin.x)/visibleSize.width) < 0.06 && std::abs(objLoc.y-(pos.y-origin.y)/visibleSize.height) < 0.06)
        {
            _objects[this->obj]->runAction(Spawn::create(ScaleBy::create(0.4, 1.4, 1.4), FadeOut::create(0.4), nullptr));
            
            // Jefferson
            
            auto jefferson = Sprite::create(JEFFERSONIMAGE);
            
            jefferson->setPosition(Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y));
            jefferson->setScale( 0.17*visibleSize.width/jefferson->getContentSize().width, 0.17*visibleSize.width/jefferson->getContentSize().width);
            
            this->addChild(jefferson,-1);
            
            jefferson->setOpacity(0);
            
            jefferson->runAction(Sequence::create(DelayTime::create(0.8), MoveTo::create(0.2, Vec2(objLoc.x*visibleSize.width, (objLoc.y + 0.1)*visibleSize.height)), Spawn::create(ScaleTo::create(0.2, 0.15*visibleSize.width/jefferson->getContentSize().width, 0.15*visibleSize.width/jefferson->getContentSize().width),FadeIn::create(0.2), EaseBounceOut::create(MoveBy::create(1, Vec2(0, -0.1*visibleSize.height))), RotateBy::create(0.75, 360), nullptr), DelayTime::create(0.4), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
            
            //
            
            objFound[obj] = true;
            
            //// check if all the objects were placed on the screen
            if (objFound[0] == true && objFound[1] == true && objFound[2] == true && objFound[3] == true && objFound[4] == true && objFound[5] == true) {
                
                /// go to next scene
                this->scheduleOnce(schedule_selector(Ch4Drag::finishChapterButtonsAppear), 2);
            }
        } else {
            
            //// reset the object to the top bar
            _objects[this->obj]->runAction(Spawn::create(ScaleTo::create(0.4, 0.1*visibleSize.width/siz.width, 0.1*visibleSize.width/siz.height), Sequence::create(FadeOut::create(0.4), MoveTo::create(0.2,Vec2(visibleSize.width*(this->obj+1)/7 + origin.x,visibleSize.height*0.88 + origin.y)), FadeIn::create(0.4), nullptr), nullptr));
        }
        return true;
    };
    
    FrameNav frameNav;
    frameNav.tapScreen(this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

void Ch4Drag::finishChapterButtonsAppear(float dt)
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
                                              CC_CALLBACK_1(Ch4Drag::gotoChapter5Callback, this));
    
    gotoChapter3->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height/2 + origin.y));
    gotoChapter3->setScale( 0.1*visibleSize.width/gotoChapter3->getContentSize().width, 0.2*visibleSize.width/gotoChapter3->getContentSize().height );
    
    auto repeatChapter2 = MenuItemImage::create(
                                                NAVLEFTON,
                                                NAVLEFTOFF,
                                                CC_CALLBACK_1(Ch4Drag::repeatChapter4Callback, this));
    
    repeatChapter2->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height/2 + origin.y));
    repeatChapter2->setScale( 0.1*visibleSize.width/repeatChapter2->getContentSize().width, 0.2*visibleSize.width/repeatChapter2->getContentSize().height );
    
    
    // create menu, it's an autorelease object
    auto frameButtons = Menu::create(gotoChapter3, repeatChapter2, NULL);
    frameButtons->setPosition(Vec2::ZERO);
    frameButtons->setOpacity(0);
    
    this->addChild(frameButtons, 1);
    
    auto appear = FadeIn::create(0.2);
    frameButtons->runAction(appear);
    
    this->scheduleOnce(schedule_selector(Ch4Drag::explanationsAppear), 0.2);
    
    this->scheduleOnce(schedule_selector(Ch4Drag::gotonextScene), 2*LAUNCHTRANSITIONTIME);
    
}

void Ch4Drag::explanationsAppear(float dt)
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