#include "City.h"
#include "cocostudio/CocoStudio.h"
#include "UITextField.h"
#include "manager/UIManager.h"
#include "global.h"
#include "util/StringUtil.h"
#include "../map/CityLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

City::City(void)
{

}

City::~City(void)
{

}

void City::playIndex(const int frame)
{
	btn->loadTextureNormal(StringUtil::StringAddInt(CITY_ICON,frame)+".png");

}

void City::update(float time)
{

}

void City::upLevel()
{

}

bool City::init()
{
	if (!Node::init())
	{
		return false;
	}
	btn=Button::create();
	playIndex(5);
	btn->addTouchEventListener(this,toucheventselector(City::onTouchEvent));
	label = Label::create("", "arial", 18);
	label->setColor(Color3B::WHITE);  
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	//设置内部颜色为黄色  
	label->setPosition(0,0);
	label->enableShadow();

	addChild(btn);
	addChild(label);
	return true;
}

void City::setLabel(string text)
{
	label->setString(text);
}

void City::onTouchEvent(Ref* pSender, TouchEventType type)
{
	if (type==TOUCH_EVENT_ENDED)
	{
		UIManager::getInstance()->open(CityLayer::create());
	}
}
