#include "BlockSprite.h"


BlockSprite::BlockSprite(void)
{
	action=nullptr;
}

BlockSprite::~BlockSprite(void)
{
	complete=nullptr;
}

Animation* BlockSprite::createAnimation(std::string prefixName, float delay)
{
	Vector<SpriteFrame*> animFrames;

	char buffer[50];
	for (int i = 1; i <= 1000; i++)
	{
		sprintf(buffer, "_%02d.png",  i);
		string str =  prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		if (frame==nullptr)break;
		animFrames.pushBack(frame);
	}

	return Animation::createWithSpriteFrames(animFrames, delay);
}

BlockSprite* BlockSprite::createBlock(string fameName, float delay,bool isloop)
{
	BlockSprite* ret=new BlockSprite();
	if (ret&&ret->initBlock(fameName,delay,isloop))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void BlockSprite::onPlay()
{
	this->stopAllActions();

	if (isloop)
	{
		this->runAction(RepeatForever::create(Animate::create(action)));
	}else{
		auto pCallback = CallFunc::create(CC_CALLBACK_0(BlockSprite::onStop,this));
		this->runAction(Sequence::create(Animate::create(action),pCallback,NULL));
	} 
}

bool BlockSprite::initBlock(string fameName, float delay, bool isLoop)
{
	this->fameName=fameName;
	this->isloop=isLoop;
	this->delay=delay;
	Sprite::initWithSpriteFrameName(fameName+"_01.png");

	action=AnimationCache::getInstance()->getAnimation(fameName);
	if (action==nullptr)
	{	
		action =createAnimation(fameName,delay);
		AnimationCache::getInstance()->addAnimation(action,fameName);
	}
	return true;
}

void BlockSprite::onStop()
{
	if (complete)
	{
		complete(this);
	}
}
