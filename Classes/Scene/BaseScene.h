#ifndef  __BASESCENE_H__
#define  __BASESCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class BaseScene:public cocos2d::Layer
{
public:
	BaseScene(void);
	~BaseScene(void);
	virtual void onEnter();

	virtual void onExit();

	virtual void runScene();
};

#endif