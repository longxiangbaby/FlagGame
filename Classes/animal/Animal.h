#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "AnimalVO.h"
#include "common/Bloodbar.h"
#include "AnimalSprite.h"
#include "fight/TileGroup.h"
#include "fight/Tile.h"
#include "skill/Skill.h"
#include "skill/SkillVO.h"
#include <iostream>
#include "control\GTween.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TileGroup;
class Skill;
class GTile;
class Camp;
class Team;

class Animal:public cocos2d::Ref
{
public:
	Animal(void);
	~Animal(void);

	static Animal* create();

	virtual void addSkill(Skill* val,int index);

	virtual Skill* getSkill(int index);

	virtual SkillVO* getSkillVO(int index);
	/**
	* 是否可移动 
	* @return 如果可以那么返回下一节点
	* 
	*/
	virtual GTile* isSteps(int step);
	/**
	* 获取技能数量
	* @return 
	* 
	*/
	virtual int getSkillSize();
	//站立焦点
	virtual GTile* getFocus();

	virtual AnimalVO* getAnimalVO();

	virtual string getRace();

	virtual void setAnimalVO(AnimalVO* val);
	//切换技能，对应技能索引
	virtual void swichSkill(int index);
	//获得选中技能
	virtual Skill* getSelectSkill();

	virtual int getSelectSkillIndex();

	virtual void setSelectSkillIndex(int index);

	virtual void showSkillArea(GTile* tile,bool isRestore);

	virtual AnimalSprite* getAnimalSprite();

	virtual bool isAttack();

	virtual void onAction(string actinName,bool isWait);

	virtual void onSkill();

	virtual void onWait();

	virtual bool onMove();

	virtual bool onDead();

	virtual void update();

	virtual void setDirect(int val);

	virtual int getDirect();	

	virtual void setStand(GTile* tile);

	virtual TileGroup* getStands();

	virtual Camp* getCamp();

	virtual vector<string> getSkillPaths();

	virtual void setCamp(Camp* camp);

	virtual bool init();

	virtual void onEnter();

	virtual void onExit();

	virtual void setHP(int curhp);

	virtual int getHP();

	virtual void setMP(int curmp);

	virtual int getMP();

protected:
	virtual void onActionEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);

	virtual void onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex);

public:
	bool isDead;
	bool isTurnEnd;
private:
	int hp;
	int mp;
protected:
	CC_SYNTHESIZE(int,step,Step);
	CC_SYNTHESIZE(int,sort,Sort);
	CC_SYNTHESIZE(int,maxHP,MaxHP);
	CC_SYNTHESIZE(int,maxMP,MaxMP);

	int getSpeed() const;
	int direct;
	AnimalSprite* p_vanimal;
	AnimalVO* p_animalVO;
	TileGroup* p_stands;
	Skill* p_skill;
	int skillIndex;
	Map<int,Skill*> m_skills;
	Camp* p_camp;
};
#endif
