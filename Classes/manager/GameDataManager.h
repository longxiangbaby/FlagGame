#ifndef __GAMEDATAMANAMGER_H__
#define __GAMEDATAMANAMGER_H__
#include "tinyxml2\tinyxml2.h"
#include <iostream>
#include <map>
#include "animal\Animal.h"
#include "skill\SkillVO.h"
#include "cocos2d.h"
#include "skill\Skill.h"
#include "util\StringUtil.h"
#include "city\City.h"

USING_NS_CC;
using namespace std;

struct HeroStruct
{
	int id;
	string name;
	string path;
	int race;
	int icon;
	int vit;//体力
	int force;//武力
	int wit;//智力
	int quk;//敏捷
	int def;//防御
	int dodge;//闪避
	string skills;
};

struct SkillStruct
{
	int id;
	string name;
	int icon;
	string path;//对应
	int mp;//消耗mp
	int action;
	string describe;
	int areaType;//范围类型
	int atkType;//攻击类型
	HurtValue hurtType;//伤害类型
	int numBuff;//buff几率
	int numTurn;//持续回合
	ADDValue addValue;
	vector< vector<int> > areas;
	string music;
};

struct Resource
{
	int lv;
	int money;
	int bing;
	int food;
	int wood;
	int iron;
};

class GameDataManager:public Ref
{
public:
	GameDataManager(void);
	~GameDataManager(void);

	static GameDataManager* getInstance();
	
	bool loadXML();

	bool loadHeroXML();

	bool loadSkillXML();

	City * getCity(int id);

	Animal* getAnimal(int id,int direct,int level=1);

	AnimalVO* getAnimalVO(int id,int level=1);

	Skill* getSkill(int id);

	SkillVO* getSkillVO(int id);

	string getString(string key);

	Resource getResorce(int lv);

	static string getText(string key);

	void destroy();

private:
	map<int,HeroStruct> m_heros;
	map<int,SkillStruct> m_skills;
	map<string,string> m_configs;

};
#endif
