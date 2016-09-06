#ifndef __BASEBTN_H__
#define __BASEBTN_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <iostream>

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

class BaseBtn:public cocos2d::Node
{
public:
	BaseBtn(void);
	~BaseBtn(void);

	static BaseBtn* createBtn(Widget* btn);

	virtual Widget* getChildByName(string name);

	virtual void destroy();

public:
	std::function<void(TouchEventType,Widget*,int,string)> doTouchEvent;
protected:
	virtual void addEvent();

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	virtual void remove();

	virtual bool initBtn(Widget* target);
protected:
	int u_id;
	string u_name;
	CC_SYNTHESIZE(Widget*,target,Target);
};
#endif
