#ifndef __TEAM_H__
#define __TEAM_H__
#include <iostream>
#include "animal\Animal.h"
#include "cocos2d.h"
#include "util\HashMap.h"

USING_NS_CC;
using namespace std;

class Animal;
class Camp;

/* 小组 */
class Team:public cocos2d::Ref
{
public:
	Team(void);
	~Team(void);

	static Team* create(); 

	bool init();

	void update(float delta);
	/**
	* 添加到小组中
	* @param animal 怪物
	* @param round 对应回合
	* @param index 对应位置
	* @return 
	* 
	*/
	void addAnimal(Animal* animal,int round,int index);

	void removeAnimal(Animal* animal);

	Vector<Animal*> getAnimals(int round);

	vector<string> getSkillPaths();

	vector<string> getRolePaths();

	int getSize();

	int getTeamID();
private:
	HashMap<int,Vector<Animal*>> m_teams;//后备队列，
	vector<string> skill_paths;
	vector<string> role_paths;
};
#endif
