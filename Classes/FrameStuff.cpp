#include "FrameStuff.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

USING_NS_CC;

FrameNav::FrameNav()
{

}

void FrameNav::addFrameNav( cocos2d::Layer *chapterLayer)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto frameImage = Sprite::create(FRAMEIMAGE);
    
    frameImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    frameImage->setScale( visibleSize.width/frameImage->getContentSize().width, visibleSize.height/frameImage->getContentSize().height );
    frameImage->setOpacity(0);

    chapterLayer->addChild(frameImage, 1);
    
    //// Create menu items for the frame
    
    auto gotoMainMenu = MenuItemImage::create(
                                           HOMEON,
                                           HOMEOFF,
                                              CC_CALLBACK_1(FrameNav::gotoMainMenuCallback, this, chapterLayer));
    
    gotoMainMenu->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height*19/20 + origin.y));
    gotoMainMenu->setScale( 0.06*visibleSize.width/gotoMainMenu->getContentSize().width, 0.06*visibleSize.width/gotoMainMenu->getContentSize().height );

    auto gotoChapters = MenuItemImage::create(
                                              VOLUMEON,
                                              VOLUMEOFF,
                                              CC_CALLBACK_1(FrameNav::toggleSound, this, chapterLayer));
    
    gotoChapters->setPosition(Vec2(visibleSize.width*154/160 + origin.x, visibleSize.height*19/20 + origin.y));
    gotoChapters->setScale( 0.06*visibleSize.width/gotoChapters->getContentSize().width, 0.06*visibleSize.width/gotoChapters->getContentSize().height );
    
    auto gotoStars = MenuItemImage::create(
                                              STARSON,
                                              STARSOFF,
                                              CC_CALLBACK_1(FrameNav::gotoMainMenuCallback, this, chapterLayer));
    
    gotoStars->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height*1.5/20 + origin.y));
    gotoStars->setScale( 0.06*visibleSize.width/gotoStars->getContentSize().width, 0.06*visibleSize.width/gotoStars->getContentSize().height );
    
    auto gotoNotes = MenuItemImage::create(
                                              NOTESON,
                                              NOTESOFF,
                                              CC_CALLBACK_1(FrameNav::exitCallback, this));
    
    gotoNotes->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height*1.5/20 + origin.y));
    gotoNotes->setScale( 0.06*visibleSize.width/gotoNotes->getContentSize().width, 0.06*visibleSize.width/gotoNotes->getContentSize().height );
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(gotoMainMenu, gotoChapters, NULL); // removed gotoStars and gotoNotes
    menu->setPosition(Vec2::ZERO);
    menu->setOpacity(0);
    
    chapterLayer->addChild(menu, 2);
    
    auto appear = FadeIn::create(0.2);
    frameImage->runAction(appear);
    auto appear2 = FadeIn::create(0.2);
    menu->runAction(appear2);

}

void FrameNav::addFrameNavNoDelay( cocos2d::Layer *chapterLayer)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto frameImage = Sprite::create(FRAMEIMAGE);
    
    frameImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    frameImage->setScale( visibleSize.width/frameImage->getContentSize().width, visibleSize.height/frameImage->getContentSize().height );
    
    chapterLayer->addChild(frameImage, 1);
    
    //// Create menu items for the frame
    
    auto gotoMainMenu = MenuItemImage::create(
                                              HOMEON,
                                              HOMEOFF,
                                              CC_CALLBACK_1(FrameNav::gotoMainMenuCallback, this, chapterLayer));
    
    gotoMainMenu->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height*19/20 + origin.y));
    gotoMainMenu->setScale( 0.06*visibleSize.width/gotoMainMenu->getContentSize().width, 0.06*visibleSize.width/gotoMainMenu->getContentSize().height );
    
    auto gotoChapters = MenuItemImage::create(
                                              VOLUMEON,
                                              VOLUMEOFF,
                                              CC_CALLBACK_1(FrameNav::toggleSound, this, chapterLayer));
    
    gotoChapters->setPosition(Vec2(visibleSize.width*154/160 + origin.x, visibleSize.height*19/20 + origin.y));
    gotoChapters->setScale( 0.06*visibleSize.width/gotoChapters->getContentSize().width, 0.06*visibleSize.width/gotoChapters->getContentSize().height );
    
    auto gotoStars = MenuItemImage::create(
                                           STARSON,
                                           STARSOFF,
                                           CC_CALLBACK_1(FrameNav::gotoMainMenuCallback, this, chapterLayer));
    
    gotoStars->setPosition(Vec2(visibleSize.width*5/160 + origin.x, visibleSize.height*1.5/20 + origin.y));
    gotoStars->setScale( 0.06*visibleSize.width/gotoStars->getContentSize().width, 0.06*visibleSize.width/gotoStars->getContentSize().height );
    
    auto gotoNotes = MenuItemImage::create(
                                           NOTESON,
                                           NOTESOFF,
                                           CC_CALLBACK_1(FrameNav::exitCallback, this));
    
    gotoNotes->setPosition(Vec2(visibleSize.width*155/160 + origin.x, visibleSize.height*1.5/20 + origin.y));
    gotoNotes->setScale( 0.06*visibleSize.width/gotoNotes->getContentSize().width, 0.06*visibleSize.width/gotoNotes->getContentSize().height );
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(gotoMainMenu, gotoChapters, NULL); //removed gotoStars and gotoNotes
    menu->setPosition(Vec2::ZERO);
    
    chapterLayer->addChild(menu, 2);
    
}

void FrameNav::gotoMainMenuCallback(cocos2d::Ref* pSender, cocos2d::Layer *chapterLayer)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    chapterLayer->unscheduleAllCallbacks();
    
    auto mainMenuScene = MainMenu::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(2, mainMenuScene));
}

void FrameNav::toggleSound(cocos2d::Ref* pSender, cocos2d::Layer *chapterLayer)
{
    
    auto vol = 0.7f*(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC)+0.15f;
    auto volEffects = 0.7f*CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()+0.15f;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto volumeControl = DrawNode::create();
    
    // background color for volume bars
    volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    // volume level for music
    volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
    
    // volume level for effects
    volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
    
    volumeControl->setOpacity(0);

    chapterLayer->addChild(volumeControl);
    
    auto jefferson = Sprite::create(JEFFERSONIMAGE);
    
    jefferson->setPosition(Vec2(visibleSize.width*0.81f + origin.x, visibleSize.height*0.90f + origin.y));
    jefferson->setScale( 0.1f*visibleSize.width/jefferson->getContentSize().width, 0.1f*visibleSize.width/jefferson->getContentSize().height );
    
    chapterLayer->addChild(jefferson);
    
    jefferson->runAction(Sequence::create(DelayTime::create(1.4f), RemoveSelf::create(), nullptr));
    
    auto eventDispatcher = chapterLayer->getEventDispatcher();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [volumeControl, origin, jefferson](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto vol = 0.7f*(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC)+0.15f;
        auto volEffects = 0.7f*CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()+0.15f;
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto audioLevel = clampf((touch->getLocation().y - origin.y)/visibleSize.height,0.0f,1.0f);
        volumeControl->stopAllActions();
        jefferson->stopAllActions();
        volumeControl->clear();
        
        // background color for volume bars
        volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
        
        volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
        
        if (touch->getLocation().x/visibleSize.width>0.845){
            
            // volume level for music
            volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
            
            // volume level for effects
            volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
            
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(VOLUMEMUSIC*(clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
        
        } else if (touch->getLocation().x/visibleSize.width>0.745){
            
            // volume level for music
            volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
            
            // volume level for effects
            volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
            
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
            
        } else {
            
            jefferson->setOpacity(0);
            volumeControl->clear();
            return false;
        }
        
        return true;
    };
    
    listener->onTouchMoved = CC_CALLBACK_2(FrameNav::onTouchMoved, this, volumeControl);
    
    listener->onTouchEnded = [volumeControl, jefferson](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto vol = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC;
        auto volEffects = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
        
        UserDefault * def = UserDefault::getInstance();
        def->setFloatForKey("MUSICVOLUME", vol);
        def->setFloatForKey("EFFECTSVOLUME", volEffects);
        def->flush();
        
        volumeControl->runAction(Sequence::create(FadeOut::create(0.4), RemoveSelf::create(), nullptr));
        jefferson->runAction(Sequence::create(DelayTime::create(0.4), RemoveSelf::create(), nullptr));
        return true;
    };
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, volumeControl);
    
    volumeControl->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(0.6), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
}

bool FrameNav::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::DrawNode *node)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vol = 0.7f*(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC)+0.15f;
    auto volEffects = 0.7f*CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()+0.15f;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto audioLevel = clampf((touch->getLocation().y - origin.y)/visibleSize.height,0.0f,1.0f);
    node->clear();
    // background color for volume bars
    node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    if (touch->getLocation().x/visibleSize.width>0.845){
        
        // volume level for music
        node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
        
        // volume level for effects
        node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(VOLUMEMUSIC*(clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
        
    } else if (touch->getLocation().x/visibleSize.width>0.745){
        
        // volume level for music
        node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
        
        // volume level for effects
        node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
        
    } else {
    
        // volume level for music
        node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
        
        // volume level for effects
        node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
    }
    
    return true;
}

void FrameNav::tapScreen(cocos2d::Layer *chapterLayer)
{
    auto tapSprite = Sprite::create(TAPTHESCREEN);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    tapSprite->setPosition(Vec2(visibleSize.width*0.5 + origin.x,visibleSize.height*0.5 + origin.y));
    tapSprite->setScale( 0.15*visibleSize.width/tapSprite->getContentSize().width, 0.15*visibleSize.width/tapSprite->getContentSize().height);
    
    chapterLayer->addChild(tapSprite,5);
    
    tapSprite->setOpacity(0);
    
    tapSprite->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(0.2), FadeOut::create(0.4), FadeIn::create(0.4), DelayTime::create(0.2), FadeOut::create(0.4), FadeIn::create(0.4), DelayTime::create(0.2), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
    
}

void FrameNav::exitCallback(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    Director::getInstance()->getRunningScene()->unscheduleAllCallbacks();
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
