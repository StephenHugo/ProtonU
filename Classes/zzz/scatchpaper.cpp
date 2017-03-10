/*

//// preload sound effects
 
CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICKSOUND);
 
//// listen for clicks

auto listener = EventListenerTouchOneByOne::create();

listener->setSwallowTouches(true);

listener->onTouchBegan = CC_CALLBACK_2(Ch1::onTouchBegan, this);

_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

//// on click function

// in header // bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
 
bool Ch1::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CLICKSOUND);
    
    return true;
}

//// Volume
 
CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
 
auto vol = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
 
log("%f",vol);
 
 
 JSON stuff
 
 #include <vector>
 #include "spine/Json.h"

 // The data will be placed in the buffer.
 std::vector<char> * buffer = response->getResponseData( );
 char *concatenated = ( char * ) malloc( buffer->size( ) + 1 );
 std::string s2( buffer->begin( ), buffer->end( ) );
 strcpy( concatenated, s2.c_str( ) );
 
 // JSON Parser
 Json *json = Json_create( concatenated );
 int test1 = Json_getInt( json, "a", -1 );
 const char *test2 = Json_getString( json, "b", "default" );
 float test3 = Json_getFloat( json, "c", -1.0f );
 
 // View the console
 log( "HTTP Response : key a : %i", test1 );
 log( "HTTP Response : key b : %s", test2 );
 log( "HTTP Response : key c : %f", test3 );
 
 // Delete the JSON object
 Json_dispose( json );
 
*/

/* Potential Issues

background music does not play, but sound effects still play: audio buffer of device full/restart device

*/

//node->setPositionY(clampf(touch->getLocation().y-vol*visibleSize.height,(0.15-vol)*visibleSize.height, (0.8-vol)*visibleSize.height));