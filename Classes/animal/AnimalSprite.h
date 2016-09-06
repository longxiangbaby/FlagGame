#ifndef __ANIMALSPRITE_H__
#define __ANIMALSPRITE_H__

#include <iostream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "common/Bloodbar.h"

using namespace std;
using namespace cocostudio;

class AnimalSprite:public cocos2d::Node
{
public:
	AnimalSprite(void);
	~AnimalSprite(void);

	static AnimalSprite* create(Armature* armature,int MaxHP);

	void setCurValue(int val);
	void setMaxValue(int maxValue);

	void setArmature(Armature* armature);

	void play(string action,bool isLoop=true);

	Armature* getArmature();

	virtual void update(float delta);

	void setFace(int scale);

protected:
	virtual void onActionEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);

	virtual void onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex);
public:
	std::function<void(Armature*,MovementEventType,string)> actionEvent;
	std::function< void(Bone *,string, int, int)> 	frameEvent;
	bool init(Armature* armature,int MaxHP);

private:
	Bloodbar* p_bloodbar;
	Armature* p_armature;
};
#endif
