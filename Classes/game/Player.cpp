#include "Player.h"
#include "Global.h"
#include "manager\GameDataManager.h"


Player::Player(void)
{
	setFlag(PLAYER);
	setState(5);
}

Player::~Player(void)
{
	CCLOG("GGrid is destroy!");

}

Player* Player::createPlayer()
{
	Player* player=new Player();
	if (player&&player->init())
	{
		//player->autorelease();
	} 
	return player;
}

bool Player::init()
{
	Animal*	animal1=GameDataManager::getInstance()->getAnimal(30012,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal2=GameDataManager::getInstance()->getAnimal(30030,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal3=GameDataManager::getInstance()->getAnimal(30096,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal4=GameDataManager::getInstance()->getAnimal(30106,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal5=GameDataManager::getInstance()->getAnimal(30005,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);
	Animal*	animal6=GameDataManager::getInstance()->getAnimal(30028,(flag!=PLAYER)?DIRECT_LEFT:DIRECT_RIGHT);

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

	CCLOG("Team size:%d",p_teamOne->getSize());

	return true;
}

