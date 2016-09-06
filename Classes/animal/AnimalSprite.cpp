#include "AnimalSprite.h"

AnimalSprite::AnimalSprite(void)
{
	p_armature=nullptr;
	p_bloodbar=nullptr;
}


AnimalSprite::~AnimalSprite(void)
{
	//p_armature->getAnimation()->setMovementEventCallFunc(NULL,NULL);
	p_armature=nullptr;
	p_bloodbar=nullptr;
	actionEvent=nullptr;
	CCLOG("AnimalSprite is destroy!");

}

AnimalSprite* AnimalSprite::create(Armature* armature,int MaxHP)
{
	AnimalSprite* p_vanimal=new AnimalSprite();
	if (p_vanimal&&p_vanimal->init(armature,MaxHP))
	{
		p_vanimal->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(p_vanimal);
	}
	return p_vanimal;
}

bool AnimalSprite::init(Armature* armature,int MaxHP)
{
	p_armature=armature;
	Sprite* bar=Sprite::createWithSpriteFrameName("blood0001.png");
	Sprite* back=Sprite::createWithSpriteFrameName("blood0002.png");
	p_bloodbar=Bloodbar::create(back,bar,MaxHP);
	p_bloodbar->setPosition(-40,armature->getAnchorPoint().y+60);

	addChild(p_armature);
	addChild(p_bloodbar);
	return true;
}

void AnimalSprite::setCurValue(int val)
{
	p_bloodbar->setValue(val);
}

void AnimalSprite::setMaxValue(int maxValue)
{
	p_bloodbar->setMaxValue(maxValue);
}

void AnimalSprite::setArmature(Armature* armature)
{
	p_armature=armature;
}

Armature* AnimalSprite::getArmature()
{
	return p_armature;
}

void AnimalSprite::update(float delta)
{

}

void AnimalSprite::play(std::string action,bool isLoop)
{
	p_armature->getAnimation()->play(action);
	p_armature->getAnimation()->setMovementEventCallFunc((isLoop)?nullptr:this,(isLoop)?nullptr:movementEvent_selector(AnimalSprite::onActionEvent));
	p_armature->getAnimation()->setFrameEventCallFunc(this,frameEvent_selector(AnimalSprite::onFrameEvent));

}

void AnimalSprite::setFace(int scale)
{
	p_armature->setScaleX(scale);
}

void AnimalSprite::onActionEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (actionEvent)
		actionEvent(armature,movementType,movementID);

}

void AnimalSprite::onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex)
{
	if (frameEvent)
		frameEvent(bone,evt,originFrameIndex,currentFrameIndex);
}


