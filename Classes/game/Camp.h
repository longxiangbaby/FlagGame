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
	//Ӣ������
	virtual int getNumHero();
	//����С��ӳ�ID����ȡС��
	virtual Team* getTeam(int id);
	//���С��
	virtual void addTeam(Team* team);

	virtual void removeTeam(Team* team);

	virtual void addCity(City* city);

	virtual void removeCity(City* city);

	virtual City* getCity(int id); 
protected:
	Map<int,Team*> m_teams;//ӵ�е�С��
	Map<int,City*> m_citys;//ӵ�еĳǳ�
	CC_SYNTHESIZE(int,flag,Flag);
	CC_SYNTHESIZE(int,state,State);

};
#endif

