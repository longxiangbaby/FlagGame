#ifndef __ICONBOX_H__
#define __ICONBOX_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <iostream>
USING_NS_CC;

using namespace std;

class IconBox:public cocostudio::Armature
{
public:
	IconBox(void);
	~IconBox(void);

	static IconBox* createIconBox(string path);

	bool initBox(string path);

	void setIndex(int index);

	int getIndex();

protected:
	int index;
};
#endif

