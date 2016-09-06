#ifndef __ICON_H__
#define __ICON_H__
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;
class Icon:public cocos2d::Ref
{
public:
	Icon(void);
	~Icon(void);
protected:
	CC_SYNTHESIZE(int,id,ID);
	CC_SYNTHESIZE(string,name,Name);
	CC_SYNTHESIZE(int,icon,Icon);
};
#endif
