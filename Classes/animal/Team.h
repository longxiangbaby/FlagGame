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

/* С�� */
class Team:public cocos2d::Ref
{
public:
	Team(void);
	~Team(void);

	static Team* create(); 

	bool init();

	void update(float delta);
	/**
	* ��ӵ�С����
	* @param animal ����
	* @param round ��Ӧ�غ�
	* @param index ��Ӧλ��
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
	HashMap<int,Vector<Animal*>> m_teams;//�󱸶��У�
	vector<string> skill_paths;
	vector<string> role_paths;
};
#endif
