#ifndef __FRAME_NAV_H__
#define __FRAME_NAV_H__

#include "cocos2d.h"

class FrameNav : public cocos2d::Layer
{
public:
    
    FrameNav();
    
    //// these functions add the blue frame with menu and volume buttons
    
    void addFrameNav( cocos2d::Layer *layer); // Fades in over 0.2 seconds
    void addFrameNavNoDelay( cocos2d::Layer *layer); // No fade-in time
    
    //// these are callbacks for the frame buttons, they decide what happens after a button is clicked
    
    void gotoMainMenuCallback(cocos2d::Ref* pSender, cocos2d::Layer *chapterLayer);
    
    // implement stars menu?
    
    void exitCallback(cocos2d::Ref* pSender); // temporary
    
    void toggleSound(cocos2d::Ref* pSender, cocos2d::Layer *chapterLayer); // volume controls

    bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::DrawNode *node);
    
    void tapScreen(cocos2d::Layer *chapterLayer);
};

#endif // __FRAME_NAV_H__
