#ifndef __ANIMALVO_H__
#define __ANIMALVO_H__
#include <iostream>
#include "cocos2d.h"
#include "common\Icon.h"
using namespace std;
USING_NS_CC;

struct Hurt
{
	int attack;
	int defend;
	int dodge;
	int speed;
	int life;
	int masic;
};

class AnimalVO:public Icon
{
public:
	AnimalVO(void);
	~AnimalVO(void);

	static AnimalVO* create();

	virtual vector<int> getSkills();

	virtual int getDefend();

	virtual int getAttack();

	virtual int getDodge();

	virtual int getSpeed();

	virtual int getMaxLife();

	virtual bool count();

	virtual void setSkills(vector<int> vals);

private:
	CC_SYNTHESIZE(int,level,Level);
	CC_SYNTHESIZE(int,hp,Hp);
	CC_SYNTHESIZE(int,mp,Mp);
	CC_SYNTHESIZE(string,path,Path);
	CC_SYNTHESIZE(int,race,Race);
	CC_SYNTHESIZE(int,vit,Vit);//����
	CC_SYNTHESIZE(int,force,Force);//����
	CC_SYNTHESIZE(int,wit,Wit);//����
	CC_SYNTHESIZE(int,quk,Quk);//����
	CC_SYNTHESIZE(int,def,Def);//����
	CC_SYNTHESIZE(int,dodge,Dodge);//����

	CC_SYNTHESIZE(int,moneny,Moneny);//Ǯ
	CC_SYNTHESIZE(int,maxMoneny,MaxMoneny);//Ǯ
	CC_SYNTHESIZE(int,bing,Bing);//Ǯ
	CC_SYNTHESIZE(int,maxBing,MaxBing);//Ǯ
	CC_SYNTHESIZE(int,food,Food);//Ǯ
	CC_SYNTHESIZE(int,maxFood,MaxFood);//Ǯ
	CC_SYNTHESIZE(int,wood,Wood);//Ǯ
	CC_SYNTHESIZE(int,maxWood,MaxWood);//Ǯ
	CC_SYNTHESIZE(int,iron,Iron);//Ǯ
	CC_SYNTHESIZE(int,maxIron,MaxIron);//Ǯ

	vector<int> skills;//����
	Hurt hurt;

};
#endif
