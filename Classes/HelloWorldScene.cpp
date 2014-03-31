#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
{
	_ship=NULL;
	_batchNode=NULL;
	_backgroundNode=NULL;
	_spacedust1=NULL;
	_spacedust2=NULL;
	_galaxy=NULL;
	_planetsunrise=NULL;
	_spacialanomaly1=NULL;
	_spacialanomaly2=NULL;
	_shipPointsPerSecY=0; 
	_asteroids=NULL;
	_nextAsteroid=0;
	_nextAsteroidSpawn=0;
	_shipLasers=NULL;
	_nextLaser=0;
}

HelloWorld::~HelloWorld()
{
	CC_SAFE_RELEASE_NULL(_asteroids);
	CC_SAFE_RELEASE_NULL(_shipLasers);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
   bool bRet=false;
   do 
   {
	   CC_BREAK_IF(!CCLayer::init());
	   _batchNode = CCSpriteBatchNode::create("Spritesheets/Sprites.pvr.ccz");
	   this->addChild(_batchNode,0);
	   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Spritesheets/Sprites.plist");
	   _ship=CCSprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
	   _batchNode->addChild(_ship);
	   CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	   _ship->setPosition(ccp(winSize.width/10,winSize.height/2));
	   _backgroundNode=CCParallaxNodeExtra::create();
	   this->addChild(_backgroundNode,-1);
	   _spacedust1=CCSprite::create("Backgrounds/bg_front_spacedust.png");
	   _spacedust2=CCSprite::create("Backgrounds/bg_front_spacedust.png");
	   _galaxy=CCSprite::create("Backgrounds/bg_galaxy.png");
	   _planetsunrise=CCSprite::create("Backgrounds/bg_planetsunrise.png");
	   _spacialanomaly1=CCSprite::create("Backgrounds/bg_spacialanomaly.png");
	   _spacialanomaly2=CCSprite::create("Backgrounds/bg_spacialanomaly2.png");
	   CCPoint dustSpeed=ccp(0.1,0.1);
	   CCPoint backgroundSpeed=ccp(0.05,0.05);
	   _backgroundNode->addChild(_spacedust1,0,dustSpeed,ccp(0,winSize.height/2));
	   _backgroundNode->addChild(_spacedust2,0,dustSpeed,ccp(_spacedust2->getContentSize().width,winSize.height/2));
	   _backgroundNode->addChild(_galaxy,-1,backgroundSpeed,ccp(0,winSize.height*0.7));
	   _backgroundNode->addChild(_planetsunrise,-1,backgroundSpeed,ccp(600,winSize.height*0));
	   _backgroundNode->addChild(_spacialanomaly1,-1,backgroundSpeed,ccp(900,winSize.height*0.3));
	   _backgroundNode->addChild(_spacialanomaly2,-1,backgroundSpeed,ccp(1500,winSize.height*0.9));
	   //添加星星粒子
	   this->addChild(CCParticleSystemQuad::create("Particles/Stars1.plist"));
	   this->addChild(CCParticleSystemQuad::create("Particles/Stars2.plist"));
	   this->addChild(CCParticleSystemQuad::create("Particles/Stars3.plist"));
	   //添加陨石
	   #define KNUMASTEROIDS 15 
	   _asteroids=CCArray::createWithCapacity(KNUMASTEROIDS);
	   _asteroids->retain();
	   for (int i=0;i<KNUMASTEROIDS;i++)
	   {
		   CCSprite *asteroid=CCSprite::createWithSpriteFrameName("asteroid.png");
		   asteroid->setVisible(false);
		   _batchNode->addChild(asteroid);
		   _asteroids->addObject(asteroid);
	   }
	   srand(static_cast<unsigned int> (getTimeTick()));
	   //添加激光
#define KNUMLASERS 5
	   _shipLasers=CCArray::createWithCapacity(KNUMASTEROIDS);
	   _shipLasers->retain();
	   for (int i=0;i<KNUMLASERS;i++)
	   {
		   CCSprite* laser=CCSprite::createWithSpriteFrameName("laserbeam_blue.png");
		   laser->setVisible(false);
		   _batchNode->addChild(laser);
		   _shipLasers->addObject(laser);
	   }

	   this->setTouchEnabled(true);
	   CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	   this->setAccelerometerEnabled(true);

	   /*
	   //下面这段代码是为了理解convertToWorldSpace而做的测试
	   CCNode* p=CCNode::create();
	   this->addChild(p);
	   p->setPosition(ccp(200,0));
	   p->addChild(_galaxy);
	   _galaxy->setPosition(ccp(100,_galaxy->getContentSize().height/2));
	   _galaxy->addChild(_planetsunrise);
	   _planetsunrise->setPosition(ccp(100,0));
	   _galaxy->addChild(_spacialanomaly1);
	   _spacialanomaly1->setPosition(ccp(100,_spacialanomaly1->getContentSize().height/2));
	   float testX=_galaxy->convertToWorldSpace(_planetsunrise->getPosition()).x;
	   float testx2=p->convertToWorldSpace(_planetsunrise->getPosition()).x;
	   float testx3=this->convertToWorldSpace(_planetsunrise->getPosition()).x;
	   CCLog(CCString::createWithFormat("grandson's positionX=%f,	parent's=%f,grand's=%f, world's=%f",_planetsunrise->getPositionX(),testX,testx2,testx3)->getCString());
	   //grandson's positionX=100.000000,	parent's=270.500000,grand's=300.000000, world's=100.000000
	   //理解：_galaxy图片width/2=259/2=129.5,_galaxy的anchro的x=300,则_galaxy左下角原点坐标x=170.5,_planetsunrise的坐标x=170.5+100=270.5

	   testX=_galaxy->convertToNodeSpace(_planetsunrise->getPosition()).x;
	   testx2=p->convertToNodeSpace(_planetsunrise->getPosition()).x;
	   testx3=this->convertToNodeSpace(_planetsunrise->getPosition()).x;
	   CCLog(CCString::createWithFormat("node's positionX=%f,	parent's=%f,grand's=%f, world's=%f",_planetsunrise->getPositionX(),testX,testx2,testx3)->getCString());
	   //node's positionX=100.000000,	parent's=-70.500000,grand's=-100.000000, world's=100.000000
	   testX=_galaxy->convertToWorldSpaceAR(_planetsunrise->getPosition()).x;
	   testx2=p->convertToWorldSpaceAR(_planetsunrise->getPosition()).x;
	   testx3=this->convertToWorldSpaceAR(_planetsunrise->getPosition()).x;
	   CCLog(CCString::createWithFormat("AR's positionX=%f,	parent's=%f,grand's=%f, world's=%f",_planetsunrise->getPositionX(),testX,testx2,testx3)->getCString());
	   //AR's positionX=100.000000,	parent's=400.000000,grand's=300.000000, world's=340.000000

	   testX=_galaxy->convertToWorldSpace(_spacialanomaly1->getPosition()).x;
	   testx2=p->convertToWorldSpace(_spacialanomaly1->getPosition()).x;
	   testx3=this->convertToWorldSpace(_spacialanomaly1->getPosition()).x;
	   CCLog(CCString::createWithFormat("nomaly1's positionX=%f,	parent's=%f,grand's=%f, world's=%f",_spacialanomaly1->getPositionX(),testX,testx2,testx3)->getCString());
	   //nomaly1's positionX=100.000000,	parent's=270.500000,grand's=300.000000, world's=100.000000
	   */

	   this->scheduleUpdate();

	   bRet=true;
   } while (0);
   
   return bRet;
}

void HelloWorld::update( float dt )
{
	/*float testX=_backgroundNode->convertToWorldSpace(_planetsunrise->getPosition()).x;
	float testx2=this->convertToWorldSpace(_planetsunrise->getPosition()).x;
	CCLog(CCString::createWithFormat("sun's positionX=%f,	world1=%f,world2=%f",_planetsunrise->getPositionX(),testX,testx2)->getCString());
	testX=_backgroundNode->convertToWorldSpace(_spacedust1->getPosition()).x;
	testx2=this->convertToWorldSpace(_spacedust1->getPosition()).x;
	CCLog(CCString::createWithFormat("dust's positionX=%f,	world1=%f,world2=%f",_spacedust1->getPositionX(),testX,testx2)->getCString());
	testX=_backgroundNode->convertToWorldSpace(_backgroundNode->getPosition()).x;
	testx2=this->convertToWorldSpace(_backgroundNode->getPosition()).x;
	CCLog(CCString::createWithFormat("background node's positionX=%f,	world1=%f,world2=%f",_backgroundNode->getPositionX(),testX,testx2)->getCString());

	CCLog(CCString::createWithFormat("srolll=%f",-1000*dt)->getCString());*/

	const CCPoint scrollSpeed=ccp(-1000,0);
	_backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(),ccpMult(scrollSpeed,dt)));
	CCArray *dusts=CCArray::createWithCapacity(2);
	dusts->addObject(_spacedust1);
	dusts->addObject(_spacedust2);
	CCArray *backgrounds=CCArray::createWithCapacity(4);
	backgrounds->addObject(_galaxy);
	backgrounds->addObject(_planetsunrise);
	backgrounds->addObject(_spacialanomaly1);
	backgrounds->addObject(_spacialanomaly2);
	for (int i=0;i<dusts->count();i++)
	{
		CCSprite* dust=(CCSprite*)dusts->objectAtIndex(i);
		float x=_backgroundNode->convertToWorldSpace(dust->getPosition()).x;
		float size=dust->getContentSize().width;
		if(x<-size){
			_backgroundNode->increamentOffset(ccp(size*2,0),dust);
		}
	}
	for (int i=0;i<backgrounds->count();i++)
	{
		CCSprite* b=(CCSprite*)backgrounds->objectAtIndex(i);
		float x=_backgroundNode->convertToWorldSpace(b->getPosition()).x;
		float size=b->getContentSize().width;
		if(x<-size){
			_backgroundNode->increamentOffset(ccp(2000,0),b);
		}
	}
	//TODO 以下重力感应控制飞船的方法 暂不理解
	CCSize winSize = CCDirector::sharedDirector()->getWinSize(); 

	float maxY = winSize.height - _ship->getContentSize().height/2; 

	float minY = _ship->getContentSize().height/2; 

	float diff = (_shipPointsPerSecY * dt) ; 

	float newY = _ship->getPosition().y + diff; 

	newY = MIN(MAX(newY, minY), maxY); 

	_ship->setPosition(ccp(_ship->getPosition().x, newY)); 

	//更新陨石
	float curTimeMillis=(float)getTimeTick();
	if(curTimeMillis>_nextAsteroidSpawn){
		float randMillis=randomValueBetween(0.2,1.0)*1000;
		_nextAsteroidSpawn=curTimeMillis+randMillis;
		float randY=randomValueBetween(0.0,winSize.height);
		float randDuration=randomValueBetween(2.0,10.0);
		CCSprite* asteroid=(CCSprite*)_asteroids->objectAtIndex(_nextAsteroid);
		_nextAsteroid++;
		if(_nextAsteroid>=_asteroids->count()){
			_nextAsteroid=0;
		}
		asteroid->stopAllActions();
		asteroid->setPosition(ccp(winSize.width+asteroid->getContentSize().width/2,randY));
		asteroid->setVisible(true);
		asteroid->runAction(CCSequence::create(CCMoveBy::create(randDuration,ccp(-winSize.width-asteroid->getContentSize().width,0)),CCCallFuncN::create(this,callfuncN_selector(HelloWorld::setInvasible)),NULL));
	}
	
	//碰撞检测
	CCObject* asteroidObj=NULL;
	CCObject* laserObj=NULL;
	CCARRAY_FOREACH(_asteroids,asteroidObj){
		CCSprite* asteroid=(CCSprite*)asteroidObj;
		if(!asteroid->isVisible()){
			continue;
		}
		CCARRAY_FOREACH(_shipLasers,laserObj){
			CCSprite* laser=(CCSprite*)laserObj;
			if(!laser->isVisible()){
				continue;
			}
			if(laser->boundingBox().intersectsRect(asteroid->boundingBox())){
				laser->setVisible(false);
				asteroid->setVisible(false);
				break;
			}
		}

		if(_ship->boundingBox().intersectsRect(asteroid->boundingBox())){
			_ship->runAction(CCBlink::create(1.0,9));
			asteroid->setVisible(false);
		}
	}
}

void HelloWorld::didAccelerate( CCAcceleration* pAccelerationValue )
{
	//TODO 以下重力感应控制飞船的方法 暂不理解
#define KFILTERINGFACTOR 0.1 

#define KRESTACCELX -0.6 

#define KSHIPMAXPOINTSPERSEC (winSize.height*0.5) 

#define KMAXDIFFX 0.2 

	double rollingX ; 

	// Cocos2DX inverts X and Y accelerometer depending on device orientation 

	// in landscape mode right x=-y and y=x !!! (Strange and confusing choice) 

	pAccelerationValue->x = pAccelerationValue->y ; 

	rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR)); 

	float accelX = pAccelerationValue->x - rollingX ; 

	CCSize winSize = CCDirector::sharedDirector()->getWinSize(); 

	float accelDiff = accelX - KRESTACCELX; 

	float accelFraction = accelDiff / KMAXDIFFX; 

	_shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction; 
}

float HelloWorld::randomValueBetween( float low,float high )
{
	//srand(static_cast<unsigned int> (getTimeTick()));	//应该放到init()里去
	//return rand()%(high-low+1)+low;
	//CCLog(CCString::createWithFormat("rand()=%i,rand()/RandMax=%f,rand()/RANDMAX/range=%f",rand(),(double)rand()/(double)RAND_MAX,(double)rand()/(double)RAND_MAX/(high-low))->getCString());
	return low+ (double)rand()/(double)RAND_MAX*(high-low);
}

void HelloWorld::setInvasible( CCNode* node )
{
	node->setVisible(false);
}

unsigned long HelloWorld::getTimeTick()
{
	timeval time;
	gettimeofday(&time,NULL);
	unsigned long millisecs=time.tv_sec*1000+time.tv_usec/1000;
	return millisecs;
}

bool HelloWorld::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	CCSprite* laser=(CCSprite*)_shipLasers->objectAtIndex(_nextLaser++);
	_nextLaser=_nextLaser>=_shipLasers->count()?0:_nextLaser;
	laser->setPosition(ccpAdd(_ship->getPosition(),ccp(laser->getContentSize().width/2,0)));
	laser->setVisible(true);
	laser->stopAllActions();
	laser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width,0)),CCCallFuncN::create(this,callfuncN_selector(HelloWorld::setInvasible)),NULL));
	return true;
}


