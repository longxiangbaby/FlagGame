#include "Camp.h"
#include "Global.h"
#include "manager\GameDataManager.h"
#include "animal\Animal.h"


Camp::Camp(void)
{
	setFlag(CAMP1);
	setState(6);
}


Camp::~Camp(void)
{
	m_teams.clear();
	CCLOG("Camp is destroy!");

}

Camp* Camp::createCamp()
{
	Camp* camp=new Camp();
	if (camp&&camp->init())
	{
		//camp->autorelease();
	}
	return camp;
}

int Camp::getNumHero()
{
	return 0;
}

bool Camp::init()
{
	Animal*	animal1=GameDataManager::getInstance()->getAnimal(30016,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal2=GameDataManager::getInstance()->getAnimal(30002,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal3=GameDataManager::getInstance()->getAnimal(30007,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal4=GameDataManager::getInstance()->getAnimal(30008,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal5=GameDataManager::getInstance()->getAnimal(30018,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal6=GameDataManager::getInstance()->getAnimal(30105,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);

	Team* p_teamOne=Team::create();
	p_teamOne->addAnimal(animal1,0,0);
	p_teamOne->addAnimal(animal2,0,1);
	p_teamOne->addAnimal(animal3,0,2);
	p_teamOne->addAnimal(animal4,0,3);
	p_teamOne->addAnimal(animal5,2,4);
	p_teamOne->addAnimal(animal6,2,5);


	animal1->setCamp(this);
	animal2->setCamp(this);
	animal3->setCamp(this);
	animal4->setCamp(this);
	animal5->setCamp(this);
	animal6->setCamp(this);
	addTeam(p_teamOne);
	return true;
}



Team* Camp::getTeam(int key)
{
	return m_teams.getRandomObject();
}

void Camp::addTeam(Team* team)
{
	m_teams.insert(team->getTeamID(),team);
}

void Camp::update(int date)
{

}

void Camp::removeTeam(Team* team)
{
	m_teams.erase(team->getTeamID());
}

void Camp::addCity(City* city)
{
	m_citys.insert(city->getCityVO()->getID(),city);
}

void Camp::removeCity(City* city)
{
	m_citys.erase(city->getCityVO()->getID());
}

City* Camp::getCity(int id)
{
	return m_citys.at(id);
}
