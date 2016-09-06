#include "GameControl.h"
#include "global.h"

static GameControl* p_gameControl=nullptr;

GameControl::GameControl(void):
	player(nullptr),
	isPause(true)
{

}

GameControl::~GameControl(void)
{
	CC_SAFE_DELETE(player);
	CCLOG("GameControl is destroy!");
	m_camps.clear();
}

GameControl* GameControl::getInstance()
{
	if (p_gameControl==nullptr)
	{
		p_gameControl=new GameControl();
	}
	return p_gameControl;
}

bool GameControl::init()
{
	player=Player::createPlayer();
	//addCamp(player);
	addCamp(Camp::createCamp());
	return true;
}

Player* GameControl::getPlayer()
{
	return player;
}

Camp* GameControl::getCamp(int flag)
{
	return m_camps.at(flag);
}

void GameControl::destroy()
{
	CC_SAFE_DELETE(p_gameControl);
	p_gameControl=nullptr;
}

void GameControl::addCamp(Camp* camp)
{
	if (camp->getFlag()==CampFlag::PLAYER)
	{
		player=static_cast<Player*>(camp);
	}
	m_camps.insert(camp->getFlag(),camp);
}

void GameControl::update(float delta)
{
	if (isPause)return;

	for (auto iter : m_camps)
	{
		Camp* camp=iter.second;
		camp->update(delta);
	}

	for (auto it : m_citys)
	{
		City* city=it.second;
		city->update(delta);
	}

}

void GameControl::pause()
{
	isPause=true;
}

void GameControl::start()
{
	isPause=false;
}

void GameControl::addCity(City* city)
{
	m_citys.insert(city->getCityVO()->getID(),city);
}

City* GameControl::getCity(int id)
{
	return m_citys.at(id);
}

