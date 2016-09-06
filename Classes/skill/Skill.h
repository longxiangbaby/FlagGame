#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"
#include "SkillVO.h"
#include "fight\Tile.h"
#include "common\Icon.h"
#include "common\BlockSprite.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class Animal;
class GTile;

class Skill:public cocos2d::Ref
{
public:
	Skill(void);
	~Skill(void);

	void execute();

	bool isExist();

	bool onDistance(bool isFriend,bool isCellBack=false);

	bool find(bool isFriend,bool isCellBack=false);
	
	bool findAll(bool isCellBack=false);

	void swithDirect(int direct);

	void show(GTile* tile,bool isRestore);

	void setSkillVO(SkillVO* vo);

	SkillVO* getSkillVO();

	void compele(BlockSprite* target);
protected:

	bool onExecute(Animal* animal,GTile* tile);
private:
	//CC_SYNTHESIZE(int,id,ID);
	//CC_SYNTHESIZE(string,name,Name);
	CC_SYNTHESIZE(Animal*,source,Source);

	virtual void onEnter();

	virtual void onExit();

	int type;
	SkillVO* p_skillVO;
	vector<vector<int>> areas;
};

#endif // !1