#ifndef  __ROOMLAYER_H__
#define  __ROOMLAYER_H__
#include "common\BaseLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"

using namespace ui;
USING_NS_CC;

class RoomLayer:public BaseLayer
{
public:
	RoomLayer(void);
	~RoomLayer(void);

	CREATE_FUNC(RoomLayer);

	virtual bool init();

	virtual void onTouchEvent(Ref* pSender, TouchEventType type);

};
#endif
