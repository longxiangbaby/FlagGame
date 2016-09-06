#ifndef  __MAPSCENE_H__
#define  __MAPSCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "Scene/BaseScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio; 

class MapScene :
	public BaseScene
{
public:
	MapScene(void);
	virtual ~MapScene(void);

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	CREATE_FUNC(MapScene);

	virtual void onEnter();

	virtual void onExit();

};
#endif
