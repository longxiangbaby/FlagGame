#ifndef  __LMENGLAYER_H__
#define  __LMENGLAYER_H__
#include "common\BaseLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"

using namespace ui;
USING_NS_CC;

class LMengLayer:public BaseLayer
{
public:
	LMengLayer(void);
	~LMengLayer(void);

	CREATE_FUNC(LMengLayer);

	virtual bool init();

	virtual void onTouchEvent(Ref* pSender, TouchEventType type);


};
#endif
