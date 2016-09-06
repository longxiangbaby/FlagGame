#ifndef  __ROLELAYER_H__
#define  __ROLELAYER_H__
#include "common\BaseLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"

using namespace ui;
USING_NS_CC;

class RoleLayer:public BaseLayer
{
public:
	RoleLayer(void);
	~RoleLayer(void);

	CREATE_FUNC(RoleLayer);

	virtual bool init();

	virtual void onTouchEvent(Ref* pSender, TouchEventType type);

};
#endif
