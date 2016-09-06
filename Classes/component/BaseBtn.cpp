#include "BaseBtn.h"
#include "util\StringUtil.h"


BaseBtn::BaseBtn(void)
{

}


BaseBtn::~BaseBtn(void)
{
	target->getEventDispatcher()->removeAllEventListeners();
	doTouchEvent=nullptr;
	CCLOG("BaseBtn is destroy!");

}

BaseBtn* BaseBtn::createBtn(Widget* btn)
{
	BaseBtn* baseBtn=new BaseBtn();
	if (baseBtn&&baseBtn->initBtn(btn))
	{
		baseBtn->addEvent();
		baseBtn->autorelease();
	}else{
		CC_SAFE_DELETE(baseBtn);
	}
	return baseBtn;
}

void BaseBtn::destroy()
{
}

void BaseBtn::addEvent()
{
	target->addTouchEventListener(this,toucheventselector(BaseBtn::onTouchEvent));
}

void BaseBtn::remove()
{

}

bool BaseBtn::initBtn(Widget* target)
{
	string name=target->getName();
	u_id=atoi(StringUtil::splitToStr(name,"_")[1].c_str());
	u_name=StringUtil::splitToStr(name,"_")[0];
	this->setTarget(target);
	target->setTouchEnabled(true);
	return true;
}

void BaseBtn::onTouchEvent(Ref* pSender, TouchEventType type)
{
	doTouchEvent(type,target,u_id,u_name);
}

Widget* BaseBtn::getChildByName(string name)
{
	return target->getChildByName(name.c_str());
}
