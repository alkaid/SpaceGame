#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxNodeExtra.h"

USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
	HelloWorld();
	virtual ~HelloWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

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
	float _shipPointsPerSecY; 
	CCArray* _asteroids;
	int _nextAsteroid;
	float _nextAsteroidSpawn;
	CCArray* _shipLasers;
	int _nextLaser;

	float randomValueBetween(float low,float high);
	void setInvasible(CCNode* node);
	unsigned long getTimeTick();
};

#endif // __HELLOWORLD_SCENE_H__
