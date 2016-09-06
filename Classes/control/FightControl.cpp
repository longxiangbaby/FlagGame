#include "FightControl.h"
#include "global.h"
#include "manager\GameDataManager.h"
#include "game\Player.h"
#include "manager\ResourceDataManager.h"
#include "GameControl.h"
#include "util\ArrayUtil.h"

static FightControl* p_fightcontrol=nullptr;

FightControl::FightControl(void):p_teamOne(nullptr),
	p_teamTwo(nullptr),
	p_grid(nullptr),
	p_animal(nullptr),
	round(0),
	turn(0),
	isTurn(false),
	last(nullptr),
	select(nullptr)
{

}

FightControl::~FightControl(void)
{
	selectCall=nullptr;
	p_teamOne=nullptr;
	p_teamTwo=nullptr;

	p_grid=nullptr;
	p_animal=nullptr;
	animals.clear();
	CCLOG("FightControl is destroy!");

}

FightControl* FightControl::getInstance()
{
	if (p_fightcontrol==nullptr)
	{
		p_fightcontrol=new FightControl();
	}
	return p_fightcontrol;
}


void FightControl::init()
{
	Camp* camp=GameControl::getInstance()->getCamp(CampFlag::CAMP1);
	Player* player=GameControl::getInstance()->getPlayer();
	p_teamOne=player->getTeam(0);
	p_teamTwo=camp->getTeam(0);

	p_grid->setStateToCol(5,player->getState(),DIRECT_RIGHT);
	p_grid->setStateToCol(8,camp->getState(),DIRECT_LEFT);
	recall(round);
	selectAnimal(p_teamOne->getAnimals(0).at(0));

}

void FightControl::recall(int round)
{
	Vector<Animal*> oanimals=p_teamOne->getAnimals(round);
	Vector<Animal*> tanimals=p_teamTwo->getAnimals(round);

	for (int i = 0; i < oanimals.size(); i++)
	{
		CCLOG("round:%d,size:%d",round,oanimals.size());
		Animal* oanimal=oanimals.at(i);
		call(oanimal,p_grid->getTile(i,0));
	}

	for (int i = 0; i < tanimals.size(); i++)
	{
		Animal* tanimal=tanimals.at(i);
		call(tanimal,p_grid->getTile(i,12));
	}
}

void FightControl::call(Animal* animal,GTile* tile)
{
	animals.pushBack(animal);
	p_grid->addAnimal(animal,tile);
}

void FightControl::removeAnimal(Animal* animal)
{
	animals.eraseObject(animal);
	//ArrayUtil::eraseObject(animals,animal);
	p_grid->removeAnimal(animal);
}

void FightControl::pause()
{

}

void FightControl::update(float delta)
{
	GTween::update();
	int length=animals.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		Animal* animal=animals.at(i);
		if (animal->isDead)
		{
			animals.eraseObject(animal);
		}
		animal->update();
	}
	onTurn();
}

void FightControl::setGrid(GGrid* grid)
{
	p_grid=grid;
}

GGrid* FightControl::getGrid()
{
	if (p_grid==nullptr)
	{
		p_grid=GGrid::create();
		p_grid->setPosition(50,120);
	}
	return p_grid;
}

void FightControl::nextRound()
{
	if (isTurn||(last!=nullptr&&!last->isTurnEnd))return;
	isTurn=true;
	turn=0;
	fights.clear();
	CCLOG("nextRound complete!");
	countFight();
}

void FightControl::onTurn()
{
	if (!isTurn) return;
	CCLOG("onTurn start!");

	if (p_animal!=nullptr&&!p_animal->isTurnEnd) return;
	onTrap();
	int flen=fights.size()-1;
	if(turn>flen){
		if (deads.size()!=0) return;
		onMove();
	}else{
		onSkill();
	}


	CCLOG("onTurn complete!");
}

void FightControl::onTrap()
{

}

void FightControl::onSkill()
{
	CCLOG("onSkill start!");

	p_animal=fights.at(turn++);
	if (p_animal->isDead) {
		return;
	}
	p_animal->onSkill();
	CCLOG("onSkill complete!");

}

void FightControl::onMove()
{
	CCLOG("onMove start!");

	sortOn();
	int step=0;
	int len=animals.size();
	for (int i = 0; i < len; i++) 
	{
		if (animals.at(i)->isDead) continue;

		if (animals.at(i)->onMove()&&animals.at(i)->getStep()>step) 
		{
			step=animals.at(i)->getStep();
			last=animals.at(i);
		}
	}
	roundDown();
	CCLOG("onMove complete!");
}

void FightControl::roundDown()
{
	CCLOG("roundDown start!");

	isTurn=false;
	std::sort(animals.begin(),animals.end(),CompereToSpeed());

	int length=animals.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		if (!(animals.at(i)->getCamp()->getFlag()==CampFlag::PLAYER)) 
		{
			int index=CCRANDOM_0_1()*(animals.at(i)->getSkillSize());
			Skill* skill=animals.at(i)->getSkill(index);
			animals.at(i)->setSelectSkillIndex(index);
		}
	}

	this->turn=0;
	this->p_animal=nullptr;
	this->deads.clear();
	this->last=nullptr;
	round++;
	recall(round);
	CCLOG("roundDown complete!");

}

void FightControl::sortOn()
{
	CCLOG("sortOn start!");
	
	int length=animals.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		Animal* source=animals.at(i);
		if (source->getSort()==0) 
			source->setSort((source->getDirect()==Direct::DIRECT_RIGHT)?source->getFocus()->getCol():1000-source->getFocus()->getCol());
		for (auto iter : source->getStands()->getRowTiles()) //
		{
			GTile* tile=iter.second->getNearExitAnimalTile(source->getDirect());//ÕÒ×î½üµÄ¹Ö
			for (Animal* target : tile->getTileData()->getAnimals()) //
			{
				if (target->getCamp()!=source->getCamp()) 
				{
					if (source->getAnimalVO()->getSpeed()<target->getAnimalVO()->getSpeed()) {
						target->setSort((source->getDirect()==Direct::DIRECT_RIGHT)?1000-target->getFocus()->getCol()+1:1000-source->getFocus()->getCol()+1);
					}else{
						source->setSort((source->getDirect()==Direct::DIRECT_RIGHT)?1000-target->getFocus()->getCol()+1:1000-source->getFocus()->getCol()+1);
					}
				}
			}
		}
		CCLOG("Sort1:%d,name:%s",source->getSort(),source->getAnimalVO()->getName().c_str());

	}

	std::sort(animals.begin(),animals.end(),CompereToMove());
	CCLOG("sortOn complete!");

}


void FightControl::selectAnimal(Animal* animal)
{
	select=animal;
	selectCall(select);
	select->getStands()->show(false);
}

Animal* FightControl::getSelectAnimal()
{
	return select;
}

void FightControl::destroy()
{
	CC_SAFE_DELETE(p_fightcontrol);
}

void FightControl::countFight()
{
	int length=animals.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		if (animals.at(i)->isAttack()) fights.pushBack(animals.at(i));
	}
	std::sort(fights.begin(),fights.end(),CompereToSpeed());
	CCLOG("countFight complete!");
}








