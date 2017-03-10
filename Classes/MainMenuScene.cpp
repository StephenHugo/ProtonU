#include "MainMenuScene.h"
#include "CreditsSceneContact.h"
#include "LaunchScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Ch1Scene.h"
#include "Ch2Scene.h"
#include "Ch3Scene.h"
#include "Ch4Scene.h"
#include "Ch5Scene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    //// Check if the App has been used before
    
    UserDefault * def = UserDefault::getInstance();
    auto returnVisit = def->getBoolForKey("RETURNVISIT", false); // default is a first visit
    def->getStringForKey("LANGUAGE","english");
    def->flush();
    
    //// Music
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSICMENU);
        
        this->scheduleOnce(schedule_selector(MainMenu::playMusic), 0.2);
    }
    
    if(returnVisit == false)  //// Run the Begin Story Scene on the first visit
    {
    
    def->setIntegerForKey("CURRENTCHAPTER", 0);
        
    // add a background
    auto sprite = Sprite::create(BEGINSTORYIMAGE);
        
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale( visibleSize.width/sprite->getContentSize().width, visibleSize.height/sprite->getContentSize().height );
        
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
        
    ////
        
    auto beginStory = MenuItemImage::create(
                                            BEGINSTORYBUTTON,
                                            BEGINSTORYBUTTON,
                                            CC_CALLBACK_1(MainMenu::ch1Callback, this));
        
    beginStory->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*2/5 + origin.y));
    beginStory->setScale( 0.3*visibleSize.width/beginStory->getContentSize().width, 0.2*visibleSize.height/beginStory->getContentSize().height );
        
    //// set up language options
        
    auto text = Label::createWithTTF("English", FELTFONT, visibleSize.height*1/30);
    auto text2 = Label::createWithTTF("Spanish", FELTFONT, visibleSize.height*1/30);
    auto text3 = Label::createWithTTF("Norwegian", FELTFONT, visibleSize.height*1/30);
        
    auto exitButton = MenuItemImage::create(
                                                 EXITBUTTON,
                                                 EXITBUTTON,
                                                 CC_CALLBACK_1(MainMenu::exitCallback, this));
        
    exitButton->setPosition(Vec2(visibleSize.width*0.05 + origin.x, visibleSize.height*0.95 + origin.y));
    exitButton->setScale( 0.1*visibleSize.width/exitButton->getContentSize().width, 0.1*visibleSize.width/exitButton->getContentSize().height );
        
    auto textBox = Sprite::create(TEXTBOX);
        
    textBox->setPosition(Vec2(visibleSize.width*0.86 + origin.x, visibleSize.height*0.98+ origin.y));
    textBox->setScale( 0.28*visibleSize.width/textBox->getContentSize().width, 0.12*visibleSize.height/textBox->getContentSize().height );
    textBox->setFlippedY(true);
        
    this->addChild(textBox, 1);
        
    auto englishOption = MenuItemLabel::create(text, CC_CALLBACK_1(MainMenu::toggleLanguage, this, 0));
        
    englishOption->setPosition(Vec2(visibleSize.width*0.875 + origin.x, visibleSize.height*0.96 + origin.y));
    englishOption->setColor(cocos2d::Color3B::BLACK);
        
    auto spanishOption = MenuItemLabel::create(text2, CC_CALLBACK_1(MainMenu::toggleLanguage, this, 1));
        
    spanishOption->setPosition(Vec2(visibleSize.width*0.95 + origin.x, visibleSize.height*0.96 + origin.y));
    spanishOption->setColor(cocos2d::Color3B::BLACK);
    
    auto norwegianOption = MenuItemLabel::create(text3, CC_CALLBACK_1(MainMenu::toggleLanguage, this, 2));
        
    norwegianOption->setPosition(Vec2(visibleSize.width*0.785 + origin.x, visibleSize.height*0.96 + origin.y));
    norwegianOption->setColor(cocos2d::Color3B::BLACK);
        
    // create menu, it's an autorelease object
    auto menu = Menu::create(beginStory, englishOption, spanishOption, norwegianOption, exitButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
        
    this->scheduleOnce(schedule_selector(MainMenu::gotoLaunchScene), MENUTRANSITIONTIME);
        
    }else{  //// Run the Main Menu to continue progress
    
    //// Background
    auto sprite = Sprite::create(BEGINSTORYIMAGE);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale( visibleSize.width/sprite->getContentSize().width, visibleSize.height/sprite->getContentSize().height );

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    ////
        
    auto resumeStory = MenuItemImage::create(
                                              RESUMEON,
                                              RESUMEOFF,
                                              CC_CALLBACK_1(MainMenu::resumeCallback, this));
    
    resumeStory->setPosition(Vec2(visibleSize.width*2/5 + origin.x, visibleSize.height*2/5 + origin.y));
    resumeStory->setScale( 0.2*visibleSize.width/resumeStory->getContentSize().width, 0.15*visibleSize.height/resumeStory->getContentSize().height );
    
    auto aboutButton = MenuItemImage::create(
                                            ABOUTON,
                                            ABOUTOFF,
                                            CC_CALLBACK_1(MainMenu::creditsCallback, this));
    
    aboutButton->setPosition(Vec2(visibleSize.width*3/5 + origin.x, visibleSize.height*2/5 + origin.y));
    aboutButton->setScale( 0.2*visibleSize.width/aboutButton->getContentSize().width, 0.15*visibleSize.height/aboutButton->getContentSize().height );
    
    auto ch1Button = MenuItemImage::create(
                                             CH1ON,
                                             CH1OFF,
                                             CC_CALLBACK_1(MainMenu::ch1Callback, this));
    
    auto ch2Button = MenuItemImage::create(
                                           CH2ON,
                                           CH2OFF,
                                           CC_CALLBACK_1(MainMenu::ch2Callback, this));
    
    auto ch3Button = MenuItemImage::create(
                                           CH3ON,
                                           CH3OFF,
                                           CC_CALLBACK_1(MainMenu::ch3Callback, this));
    
    auto ch4Button = MenuItemImage::create(
                                           CH4ON,
                                           CH4OFF,
                                           CC_CALLBACK_1(MainMenu::ch4Callback, this));
    
    auto ch5Button = MenuItemImage::create(
                                           CH5ON,
                                           CH5OFF,
                                           CC_CALLBACK_1(MainMenu::ch5Callback, this));
        
    this->setPosNScale(ch1Button, 3.0f/8, 0.2, 0.13, 0.13);
    this->setPosNScale(ch2Button, 4.0f/8, 0.2, 0.13, 0.13);
    this->setPosNScale(ch3Button, 5.0f/8, 0.2, 0.13, 0.13);
    this->setPosNScale(ch4Button, 6.0f/8, 0.2, 0.13, 0.13);
    this->setPosNScale(ch5Button, 7.0f/8, 0.2, 0.13, 0.13);
    
    //// set up language options
        
    auto text = Label::createWithTTF("English", FELTFONT, visibleSize.height*1/30);
    auto text2 = Label::createWithTTF("Spanish", FELTFONT, visibleSize.height*1/30);
    auto text3 = Label::createWithTTF("Norwegian", FELTFONT, visibleSize.height*1/30);
    
    auto exitButton = MenuItemImage::create(
                                                EXITBUTTON,
                                                EXITBUTTON,
                                                CC_CALLBACK_1(MainMenu::exitCallback, this));
        
    exitButton->setPosition(Vec2(visibleSize.width*0.05 + origin.x, visibleSize.height*0.95 + origin.y));
    exitButton->setScale( 0.1*visibleSize.width/exitButton->getContentSize().width, 0.1*visibleSize.width/exitButton->getContentSize().height );
    
        
    auto textBox = Sprite::create(TEXTBOX);
        
    textBox->setPosition(Vec2(visibleSize.width*0.86 + origin.x, visibleSize.height*0.98+ origin.y));
    textBox->setScale( 0.28*visibleSize.width/textBox->getContentSize().width, 0.12*visibleSize.height/textBox->getContentSize().height );
    textBox->setFlippedY(true);
        
    this->addChild(textBox, 1);
        
    auto englishOption = MenuItemLabel::create(text, CC_CALLBACK_1(MainMenu::toggleLanguage, this, 0));
        
    englishOption->setPosition(Vec2(visibleSize.width*0.875 + origin.x, visibleSize.height*0.96 + origin.y));
    englishOption->setColor(cocos2d::Color3B::BLACK);
        
    auto spanishOption = MenuItemLabel::create(text2, CC_CALLBACK_1(MainMenu::toggleLanguage, this, 1));
        
    spanishOption->setPosition(Vec2(visibleSize.width*0.95 + origin.x, visibleSize.height*0.96 + origin.y));
    spanishOption->setColor(cocos2d::Color3B::BLACK);
    
    auto norwegianOption = MenuItemLabel::create(text3, CC_CALLBACK_1(MainMenu::toggleLanguage, this, 2));
        
    norwegianOption->setPosition(Vec2(visibleSize.width*0.785 + origin.x, visibleSize.height*0.96 + origin.y));
    norwegianOption->setColor(cocos2d::Color3B::BLACK);
        
    // create menu, it's an autorelease object
    auto menu = Menu::create(resumeStory, aboutButton, ch1Button, ch2Button, ch3Button, ch4Button, ch5Button, englishOption, spanishOption, norwegianOption, exitButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    ////
    
    this->scheduleOnce(schedule_selector(MainMenu::gotoCreditsScene), MENUTRANSITIONTIME);
    
    }

    return true;
}

void MainMenu::setPosNScale(cocos2d::MenuItemImage *sprite, float xx, float yy, float sxx, float syy)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sprite->setPosition(Vec2(visibleSize.width*xx + origin.x, visibleSize.height*yy + origin.y));
    
    sprite->setScale( sxx*visibleSize.width/sprite->getContentSize().width, syy*visibleSize.width/sprite->getContentSize().height);
}

void MainMenu::playMusic(float dt)
{
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSICMENU, true);
    }
}

//// Callback to go to next scene automatically

void MainMenu::gotoCreditsScene(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto creditsScene = Launch::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
}

//// Callback to go to next scene automatically

void MainMenu::gotoLaunchScene(float dt)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto creditsScene = Launch::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
}

void MainMenu::creditsCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto creditsScene = Contact::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, creditsScene));
    
}

void MainMenu::resumeCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    UserDefault * def = UserDefault::getInstance();
    auto currentChapter = def->getIntegerForKey("CURRENTCHAPTER",0);
    
    if(currentChapter<2){
    
        auto ch1Scene = Ch1::createScene();
        Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch1Scene));
        
    }else if(currentChapter==2){
        
        auto ch2Scene = Ch2::createScene();
        Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch2Scene));
        
    }else if(currentChapter==3){
        
        auto ch3Scene = Ch3::createScene();
        Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch3Scene));
        
    }else if(currentChapter==4){
        
        auto ch4Scene = Ch4::createScene();
        Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch4Scene));
        
    }else if(currentChapter==5){
    
        auto ch5Scene = Ch5::createScene();
        Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch5Scene));
    }
}

void MainMenu::ch1Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto ch1Scene = Ch1::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch1Scene));
    
}

void MainMenu::ch2Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto ch2Scene = Ch2::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch2Scene));
    
}

void MainMenu::ch3Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto ch3Scene = Ch3::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch3Scene));
    
}

void MainMenu::ch4Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto ch4Scene = Ch4::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch4Scene));
    
}

void MainMenu::ch5Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto ch5Scene = Ch5::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, ch5Scene));
    
}

void MainMenu::exitCallback(Ref* pSender)
{
    
    this->scheduleOnce(schedule_selector(MainMenu::exitDialogue), 0.1);
    
    /*
     Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
     */
}

void MainMenu::exitDialogue(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// pop-up window asks people to tap the screen to exit
    
    auto text = Label::createWithTTF("Tap here then release over Jefferson to exit.", FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.29 + origin.x, visibleSize.height*0.72 + origin.y));
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
    textBox->runAction(Sequence::create(appear, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    auto appear2 = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear2, DelayTime::create(EXPLAINFRAMEBUTTONSTIME), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
    ////
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto x = touch->getLocation().x/visibleSize.width;
        auto y = touch->getLocation().y/visibleSize.height;
        
        //// check if they clicked the box
        if (x < 0.5f && x > 0.1f && y < 0.9f && y > 0.7f) {
            
            text->stopAllActions();
            textBox->runAction(Sequence::create(Spawn::create(ScaleBy::create(0.4, 0.2), FadeOut::create(0.4), nullptr), RemoveSelf::create() ,nullptr));
            text->runAction(Sequence::create(Spawn::create(ScaleBy::create(0.4, 0.4), FadeOut::create(0.4), nullptr), RemoveSelf::create() ,nullptr));
            //// remove the dialogue box if they hit
            
            return true;
        }
        text->stopAllActions();
        textBox->runAction(Sequence::create(FadeOut::create(0.4), RemoveSelf::create() ,nullptr));
        text->runAction(Sequence::create(FadeOut::create(0.4), RemoveSelf::create() ,nullptr));
        //// remove the dialogue box if they missed
        _eventDispatcher->removeEventListener(listener);
        return false;
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto x = touch->getLocation().x/visibleSize.width;
        auto y = touch->getLocation().y/visibleSize.height;
        
        //// Leave the game if in lower left part of screen
        if (x < 0.3f && y < 0.3f) {
            
            Director::getInstance()->end();
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
            
            return true;
            
        }
        _eventDispatcher->removeEventListener(listener);
        return true;
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

void MainMenu::toggleLanguage(cocos2d::Ref* pSender, int lang)
{
    UserDefault * def = UserDefault::getInstance();
    auto language = def->getStringForKey("LANGUAGE","english");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setScale( 0.1f*visibleSize.width/jefferson->getContentSize().width, 0.1f*visibleSize.width/jefferson->getContentSize().height );
    
    jefferson->setOpacity(0);
    
    this->addChild(jefferson,55);
    
    switch (lang) {
        case 0:
            def->setStringForKey("LANGUAGE", "english");
            
            jefferson->setPosition(Vec2(visibleSize.width*0.88f + origin.x, visibleSize.height*0.95f + origin.y));
            jefferson->runAction(Sequence::create(FadeIn::create(0.2f), DelayTime::create(0.4f), FadeOut::create(0.2f), RemoveSelf::create(), nullptr));
            
            break;
            
        case 1:
            def->setStringForKey("LANGUAGE", "spanish");
            
            jefferson->setPosition(Vec2(visibleSize.width*0.95f + origin.x, visibleSize.height*0.95f + origin.y));
            jefferson->runAction(Sequence::create(FadeIn::create(0.2f), DelayTime::create(0.4f), FadeOut::create(0.2f), RemoveSelf::create(), nullptr));
            
            break;
        
        case 2:
            def->setStringForKey("LANGUAGE", "norwegian");
            
            jefferson->setPosition(Vec2(visibleSize.width*0.79f + origin.x, visibleSize.height*0.95f + origin.y));
            jefferson->runAction(Sequence::create(FadeIn::create(0.2f), DelayTime::create(0.4f), FadeOut::create(0.2f), RemoveSelf::create(), nullptr));
            
            break;
            
        default:
            def->setStringForKey("LANGUAGE", "english");
            break;
    }
    
    def->flush();
    
}