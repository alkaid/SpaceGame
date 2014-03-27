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
	
	
}
