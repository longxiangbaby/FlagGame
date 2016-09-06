#ifndef __CHOICEBOX_H__
#define __CHOICEBOX_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"

#include <iostream>
#include "common/Icon.h"
#include "util\StringUtil.h"
#include "BaseBtn.h"
#include "IconBox.h"
#include "IconBox2.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio;
using namespace ui;

struct Item
{
	BaseBtn* component;
	Icon* data;
	IconBox2* iconBox;

	void destroy(){
		component=nullptr;
		data=nullptr;
		iconBox=nullptr;
	}
	//static Item* createItem(BaseBtn* component,Icon* data,Armature* armature){
	//	Item* item=new Item();
	//	item->component=component;
	//	item->data=data;
	//	item->armature=armature;
	//	item->autorelease();
	//	return item;
	//}
};

class ChoiceBox:public cocos2d::Node
{
public:
	ChoiceBox(void);
	~ChoiceBox(void);

	static ChoiceBox* createChoiceBox(string iconName);

	virtual void setComponents(Widget** components,int size);

	virtual void provide(Icon** datas,int size);

	virtual Item getItem(int index);

	//virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	virtual void onTouchEvent(TouchEventType type,Widget* target,int id,string name); 

	virtual void setSelectIndex(int index);

	virtual int getSelectIndex();

	virtual void destroy();
public:
	std::function<bool(Ref* data)> onTouch;
	std::function<bool(TouchEventType,Item,int,string)> onChangeEvent;
protected:
	map<int,Item> m_items;
	CC_SYNTHESIZE(string,iconName,IconName);

	//virtual void onEnter();

	//virtual void onExit();

	int selectIndex;

	int length;
};

#endif
