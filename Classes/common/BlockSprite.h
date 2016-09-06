#ifndef __BLOCKSPRITE_H__
#define __BLOCKSPRITE_H__
#include "cocos2d.h"
#include <stdio.h>
#include <iostream>

USING_NS_CC;
using namespace std;

class BlockSprite:public cocos2d::Sprite
{
public:
	BlockSprite(void);
	~BlockSprite(void);

	static BlockSprite* createBlock(string fameName, float delay, bool isLoop=false);

	virtual void onPlay();

protected:
	virtual Animation* createAnimation(std::string prefixName, float delay);

	virtual bool initBlock(string vfameName, float vdelay, bool loop);

	virtual void onStop();

public:
	std::function<void(BlockSprite*)> complete;
	bool isloop;
	float delay;
	string fameName;
protected:
	Sprite* sprite;
	Animation* action;

};
#endif
