#ifndef __RESOURCEDATAMANAGER_H__
#define __RESOURCEDATAMANAGER_H__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class ResourceDataManager:public Ref
{
public:
	ResourceDataManager(void);
	~ResourceDataManager(void);

	static ResourceDataManager* getInstance();

	bool loadAnimals();

	bool loadSources(const std::function<void()>& callback);

	bool loadRole(string name);

	bool removeRole(string name);

	bool removeRoles(vector<string> names);

	bool loadSkill(string name);

	bool removeSkills(vector<string> skills);

	bool init();

	static void destroyInstance();
};

#endif 