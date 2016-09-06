#include "AnimalVO.h"
#include "global.h"

AnimalVO::AnimalVO(void):
	hp(1000),
	mp(1000),
	level(5),
	race(Race::SOLDIERS)
{
	
}


AnimalVO::~AnimalVO(void)
{
}

AnimalVO* AnimalVO::create()
{
	AnimalVO* animalVO=new AnimalVO();
	return animalVO;
}

int AnimalVO::getDefend()
{
	return hurt.defend;
}

int AnimalVO::getAttack()
{
	return hurt.attack;
}

int AnimalVO::getDodge()
{
	return hurt.dodge;
}

int AnimalVO::getSpeed()
{
	return hurt.speed;
}

int AnimalVO::getMaxLife()
{
	return hurt.life;
}

void AnimalVO::setSkills(vector<int> vals)
{
	skills=vals;
}

vector<int> AnimalVO::getSkills()
{
	return skills;
}

bool AnimalVO::count()
{
	hurt.attack=bing*getForce()/100;
	hurt.defend=iron*getDefend()/100;
	hurt.life=food*getVit()/100;
	hurt.speed=getQuk();
	hurt.dodge=getDodge();
	hurt.masic=getWit()*wood/100;
	CCLOG("life:%d",hurt.life);
	setHp(hurt.life);
	setMp(hurt.masic);
	return true;
}

