#ifndef __FIGHTCONTROL_H__
#define __FIGHTCONTROL_H__
#include "cocos2d.h"

USING_NS_CC;

class Bloodbar :
	public cocos2d::Node
{
public:
	Bloodbar(void);
	~Bloodbar(void);

	static Bloodbar* create(Node* back,Node* bar,int maxValue);

	void setValue(int val);

	int getValue();

	void setMaxValue(int maxValue);

	int getMaxValue();

	void setBar(Node* bar);

private:
	int curValue;
	int maxValue;
	Node* p_bar;

protected:
	void updateBar();
};
#endif
