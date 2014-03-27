#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxNodeExtra.h"

USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);

private:
	CCSprite* _ship;
	CCSpriteBatchNode* _batchNode;
	CCParallaxNodeExtra *_backgroundNode;
	CCSprite* _spacedust1;
	CCSprite* _spacedust2;
	CCSprite* _galaxy;
	CCSprite* _planetsunrise;
	CCSprite* _spacialanomaly1;
	CCSprite* _spacialanomaly2;
};

#endif // __HELLOWORLD_SCENE_H__
