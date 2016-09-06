#ifndef  __CAMP_H__
#define  __CAMP_H__
#include <map>
#include "cocos2d.h"
#include "animal\Team.h"
#include "city\City.h"

USING_NS_CC;
using namespace std;   

class Team;

class Camp:public cocos2d::Ref
{
public:
	Camp(void);
	~Camp(void);

	//CREATE_FUNC(Camp);
	static Camp* createCamp();

	virtual bool init();

	virtual void update(int date);
	//英雄数量
	virtual int getNumHero();
	//根据小组队长ID，获取小组
	virtual Team* getTeam(int id);
	//添加小组
	virtual void addTeam(Team* team);

	virtual void removeTeam(Team* team);

	virtual void addCity(City* city);

	virtual void removeCity(City* city);

	virtual City* getCity(int id); 
protected:
	Map<int,Team*> m_teams;//拥有的小队
	Map<int,City*> m_citys;//拥有的城池
	CC_SYNTHESIZE(int,flag,Flag);
	CC_SYNTHESIZE(int,state,State);

};
#endif

