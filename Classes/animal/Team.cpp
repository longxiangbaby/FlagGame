#include "Team.h"
#include "util\ArrayUtil.h"
#include "global.h"


Team::Team(void)
{

}

Team::~Team(void)
{
	role_paths.clear();
	skill_paths.clear();
	m_teams.clear();
	CCLOG("Team is destroy!");

}

void Team::addAnimal(Animal* animal,int round,int index)
{
	if (!m_teams.containKey(round))
	{
		Vector<Animal*> animals;
		animals.pushBack(animal);
		m_teams.insert(round,animals);
	}else
	{
		auto iter=m_teams.find(round);
		iter->second.pushBack(animal);
		//m_teams.at(round).pushBack(animal);
	}
	string rolePath=ROLE_PATH(animal->getAnimalVO()->getPath());
	if (ArrayUtil::getIndex(role_paths,rolePath)<0)
	{
		role_paths.push_back(rolePath);
	}

	vector<string> skillPaths=animal->getSkillPaths();
	int length=skillPaths.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		string skillpath=SKILL_PATH(skillPaths[i]);

		if (ArrayUtil::getIndex(skill_paths,skillpath)<0)
		{
			CCLOG("2222path:%s",skillpath.c_str());
			skill_paths.push_back(skillpath);
		}
	}
	skillPaths.clear();
}

Vector<Animal*> Team::getAnimals(int round)
{
	return m_teams.at(round);
}

Team* Team::create()
{
	Team* team=new Team();
	if (team&&team->init())
	{
		//team->autorelease();
		return team;
	}
	CC_SAFE_DELETE(team);
	return team;
}

bool Team::init()
{
	return true;
}

void Team::removeAnimal(Animal* animal)
{

}

void Team::update(float delta)
{

}

vector<string> Team::getSkillPaths()
{
	return skill_paths;
}

vector<string> Team::getRolePaths()
{
	return role_paths;
}

int Team::getTeamID()
{
	return getAnimals(0).at(0)->getAnimalVO()->getID();
}

int Team::getSize()
{
	return m_teams.size();
}

