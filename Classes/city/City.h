#ifndef  __CITY_H__
#define  __CITY_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CityVO.h"
#include "UIButton.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class City :public cocos2d::Node
{
public:
	City(void);
	~City(void);

	CREATE_FUNC(City);

	virtual void playIndex(const int frame);

	virtual void update(float time) override;

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	virtual void upLevel();

	virtual bool init();

	virtual void setLabel(string text);

private:
	Button* btn;
	Label* label;
	CC_SYNTHESIZE(CityVO*,cityVO,CityVO);
	CC_SYNTHESIZE(int,flag,Flag);//À˘ Ù’Û”™

};
#endif

