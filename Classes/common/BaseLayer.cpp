#include "BaseLayer.h"
#include "cocostudio\CCSGUIReader.h"
#include "manager\UIManager.h"


BaseLayer::BaseLayer(void)
{

}


BaseLayer::~BaseLayer(void)
{
}

bool BaseLayer::init()
{
	root=cocostudio::GUIReader::getInstance()->widgetFromJsonFile(rootPath.c_str());
	rootPanel=static_cast<Layout*>( Helper::seekWidgetByName(root, panelName.c_str()));
	Button* close_btn=static_cast<Button*>(rootPanel->getChildByName("close_btn"));
	close_btn->addTouchEventListener(this,toucheventselector(BaseLayer::close));
	this->addChild(root);
	return true;
}

void BaseLayer::open()
{

}

void BaseLayer::close(Ref* pSender, TouchEventType type)
{
	Button* pbutton= static_cast<Button*>(pSender);

	string name=pbutton->getName();

	if (type==TOUCH_EVENT_ENDED)
	{
		if (name=="close_btn")
		{
			UIManager::getInstance()->close(this);
		}
	}
}

void BaseLayer::onTouchEvent(Ref* pSender, TouchEventType type)
{

}
