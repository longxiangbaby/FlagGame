#ifndef __ICONBOXX_H__
#define __ICONBOXX_H__
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class IconBox2:public cocos2d::Sprite
{
public:
	IconBox2(void);
	~IconBox2(void);

	static IconBox2* createBox(string path);

	bool initBox(string path);

	void setIndex(int index);

	int getIndex();
protected:
	int index;
	string path;
};
#endif

