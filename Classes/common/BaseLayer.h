#ifndef  __BASELAYER_H__
#define  __BASELAYER_H__

#include "cocos2d.h"
#include <iostream>
#include "ui/UIWidget.h"
#include "CocosGUI.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class BaseLayer:public cocos2d::Layer
{
public:
	BaseLayer(void);
	~BaseLayer(void);

	virtual bool init();

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	virtual void open();

	virtual void close(Ref* pSender, TouchEventType type);

public:
	string rootPath;
	string panelName;

protected:
	Widget* root;
	Layout* rootPanel;
};
#endif
