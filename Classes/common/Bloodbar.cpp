#include "Bloodbar.h"


Bloodbar::Bloodbar(void):
	curValue(0),
	maxValue(0)
{
	p_bar=nullptr;
}


Bloodbar::~Bloodbar(void)
{
}

Bloodbar* Bloodbar::create(Node* back,Node* bar,int maxValue)
{
	Bloodbar* bloodbar=new Bloodbar();
	bar->setAnchorPoint(Point(0,0.5));
	back->setAnchorPoint(Point(0,0.5));
	bloodbar->addChild(back);
	bloodbar->addChild(bar);
	bloodbar->setBar(bar);
	bloodbar->setMaxValue(maxValue);
	bloodbar->setValue(maxValue);
	bloodbar->autorelease();
	return bloodbar;
}

void Bloodbar::setValue(int val)
{
	this->curValue=val;
	updateBar();
}

int Bloodbar::getValue()
{
	return curValue;
}

void Bloodbar::setMaxValue(int maxValue)
{
	this->maxValue=maxValue;
	updateBar();
}

int Bloodbar::getMaxValue()
{
	return maxValue;
}

void Bloodbar::setBar(Node* bar)
{
	p_bar=bar;
}

void Bloodbar::updateBar()
{
	CCLOG("curValue:%f",(float)curValue/maxValue);
	p_bar->setScaleX((float)curValue/maxValue);
}
