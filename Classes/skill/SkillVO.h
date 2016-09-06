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
	CC_SYNTHESIZE(string,path,Path);//��Ӧ����·��
	CC_SYNTHESIZE(int,mp,MP);//����
	CC_SYNTHESIZE(int,action,Action);//����

	CC_SYNTHESIZE(string,describe,Describe);//����
	CC_SYNTHESIZE(string,music,Music);//��Ӧ����·��

	CC_SYNTHESIZE(int,areaType,AreaType);//��Χ����
	CC_SYNTHESIZE(int,atkType,AtkType);//��������
	CC_SYNTHESIZE(int,numBuff,NumBuff);//����burff����
	CC_SYNTHESIZE(int,numTurn,NumTurn);//�����غ�

	HurtValue hurtType;//�˺�����

	ADDValue addValue;

	vector< vector<int> > v_areas;//������Χ
};
#endif
