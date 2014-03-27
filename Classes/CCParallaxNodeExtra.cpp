
#include "CCParallaxNodeExtra.h"

USING_NS_CC;

//类CCPointObject从CCparallaxNode.cpp中复制而来
class CCPointObject : CCObject
{
	CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
		CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
		CC_SYNTHESIZE(CCNode *,m_pChild, Child)    // weak ref

public:
	static CCPointObject * pointWithCCPoint(CCPoint ratio, CCPoint offset)
	{
		CCPointObject *pRet = new CCPointObject();
		pRet->initWithCCPoint(ratio, offset);
		pRet->autorelease();
		return pRet;
	}
	bool initWithCCPoint(CCPoint ratio, CCPoint offset)
	{
		m_tRatio = ratio;
		m_tOffset = offset;
		m_pChild = NULL;
		return true;
	}
};

CCParallaxNodeExtra * CCParallaxNodeExtra::create()
{
	CCParallaxNodeExtra *pRet = new CCParallaxNodeExtra();
	pRet->autorelease();
	return pRet;
}

void CCParallaxNodeExtra::increamentOffset( CCPoint offset,CCNode* node )
{
	for(unsigned int i=0; i < m_pParallaxArray->num; i++ ) 
	{
		CCPointObject *point = (CCPointObject*)m_pParallaxArray->arr[i];
		CCNode* child=point->getChild();
		if(child->isEqual(node)){
			point->setOffset(ccpAdd(point->getOffset(),offset));
		}
	}
}

