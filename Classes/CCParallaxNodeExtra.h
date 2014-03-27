#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CCParallaxNodeExtra : public CCParallaxNode
{
public:
	void increamentOffset(CCPoint offset,CCNode* node);
	static CCParallaxNodeExtra * create();
};