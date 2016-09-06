#ifndef  __SKILLVO_H__
#define  __SKILLVO_H__
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "common\Icon.h"

USING_NS_CC;
using namespace std;

struct HurtValue
{
	int type;
	int value1;
	int value2;
	int value3;
};

struct ADDValue
{
	int life;
	int attack;
	int defend;
	int masic;
	int speed;
	int dodge;
};

class SkillVO:public Icon
{
public:
	SkillVO(void);
	~SkillVO(void);

	void setAreas(vector< vector<int> > vals);

	vector< vector<int> > getAreas();
	
	HurtValue getHurtValue();

	ADDValue getAddValue() const;

private:
	CC_SYNTHESIZE(string,path,Path);//对应动画路径
	CC_SYNTHESIZE(int,mp,MP);//耗蓝
	CC_SYNTHESIZE(int,action,Action);//耗蓝

	CC_SYNTHESIZE(string,describe,Describe);//描述
	CC_SYNTHESIZE(string,music,Music);//对应音乐路径

	CC_SYNTHESIZE(int,areaType,AreaType);//范围类型
	CC_SYNTHESIZE(int,atkType,AtkType);//攻击类型
	CC_SYNTHESIZE(int,numBuff,NumBuff);//附带burff几率
	CC_SYNTHESIZE(int,numTurn,NumTurn);//持续回合

	HurtValue hurtType;//伤害类型

	ADDValue addValue;

	vector< vector<int> > v_areas;//攻击范围
};
#endif
