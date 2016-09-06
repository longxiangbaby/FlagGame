#ifndef  __MAPLAYER_H__
#define  __MAPLAYER_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio; 

class MapLayer:public cocos2d::Layer
{

public:
	MapLayer(void);
	~MapLayer(void);

	static MapLayer* createMap();

	bool loadMap(const std::string &str);
	
	virtual void onEnter() override;

	virtual void onExit() override;

	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

protected:
	TMXTiledMap* p_map;

};
#endif
