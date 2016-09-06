#include "Skill.h"
#include "Global.h"
#include "control\FightControl.h"
#include "util\StringUtil.h"

Skill::Skill(void):p_skillVO(nullptr)
{

}

Skill::~Skill(void)
{
	source=nullptr;
	CC_SAFE_DELETE(p_skillVO);
	areas.clear();
	CCLOG("Skill is destroy!");
}

void Skill::execute()
{
	find(false,true);
}

void Skill::swithDirect(int direct)
{
	areas=p_skillVO->getAreas();
	if (direct==DIRECT_LEFT) 
	{
		int len=areas.size();
		for (int i = len - 1; i >= 0 ; i--)
		{
			areas[i][0]=-areas[i][0];
		}
	}
}

void Skill::show(GTile* tile,bool isRestore)
{
	int i=areas.size()-1;
	while(i>=0){
		GTile* n_tile=tile->getNeighbor(areas[i][1],areas[i][0]);
		if (n_tile!=nullptr){
			int index=(p_skillVO->getAtkType()==MDISTANCE)?((source->getDirect()==DIRECT_RIGHT)?8:9):7;
			n_tile->show((isRestore)?n_tile->getState():index);		
		}
		i--;
	}
}

void Skill::setSkillVO(SkillVO* vo)
{
	p_skillVO=vo;
}

SkillVO* Skill::getSkillVO()
{
	return p_skillVO;
}

bool Skill::isExist()
{
	return find(false,false);
}

bool Skill::onDistance(bool isFriend,bool isCellBack)
{
	int len=areas.size();

	for (int i = 0; i < len ; i++)
	{
		GTile* tile=source->getFocus()->getNeighbor(areas[i][1],areas[i][0]);
		if (tile!=nullptr){
			Vector<Animal*> animals=tile->getTileData()->getAnimals();
			int size= animals.size();

			for (int k = 0; k < size ; k++)
			{
				Animal* target=animals.at(k);
				if (!isFriend) 
				{
					if(target->getCamp()!=source->getCamp()){
						if (isCellBack) onExecute(target,tile);
						return true;
					}else{
						return false;
					}
				}
				if(isFriend){
					if(target->getCamp()==source->getCamp()){
						if (isCellBack) onExecute(target,tile);
						return true;
					}else{
						return false;
					}
				}
			}

		}
	}

	return false;
}

bool Skill::find(bool isFriend,bool isCellBack)
{
	int len=areas.size();
	Vector<Animal*> like;
	for (int i = 0; i < len ; i++)
	{
		GTile* tile=source->getFocus()->getNeighbor(areas[i][1],areas[i][0]);
		if (tile!=nullptr){
			Vector<Animal*> animals=tile->getTileData()->getAnimals();
			int size= animals.size();
			for (int k = 0; k < size ; k++)
			{
				Animal* target=animals.at(k);

				if (like.getIndex(target)>0||target->isDead) continue;

				if (!isFriend&&target->getCamp()!=source->getCamp()) 
				{
					if (isCellBack){
						onExecute(target,tile);
					}else{
						return true;
					}
				}
				if(isFriend&&target->getCamp()==source->getCamp()){
					if (isCellBack){
						onExecute(target,tile);
					}else{
						return true;
					}
				}
				like.pushBack(target);
			}

		}
	}
	like.clear();
	return false;
}

bool Skill::findAll(bool isCellBack)
{
	int len=areas.size();
	Vector<Animal*> like;
	for (int i = 0; i < len ; i++)
	{
		GTile* tile=source->getFocus()->getNeighbor(areas[i][1],areas[i][0]);
		if (tile!=nullptr){
			Vector<Animal*> animals=tile->getTileData()->getAnimals();
			int size= animals.size();

			for (int k = 0; k < size ; k++)	
			{
				Animal* target=animals.at(k);

				if (like.getIndex(target)!=-1) continue;
				if (isCellBack){
					onExecute(target,tile);
				}else{
					return true;
				}
				like.pushBack(target);
			}

		}
	}
	like.clear();
	return false;
}

void Skill::onEnter()
{

}

void Skill::onExit()
{

}

bool Skill::onExecute(Animal* animal,GTile* tile)
{
	if (animal->isDead) return true;
	BlockSprite* skillBlock=BlockSprite::createBlock(p_skillVO->getPath(),0.05f);
	skillBlock->complete=CC_CALLBACK_1(Skill::compele,this);
	FightControl::getInstance()->getGrid()->addEffctBlock(skillBlock,animal);
	skillBlock->onPlay();

	int result=CCRANDOM_0_1()*10+1;
	CCLOG("AAAAAAAAAAAAAAAAAAresult:%d",result);
	auto la = LabelAtlas::create(StringUtil::m_toStr(result), "image/labelatlas.png", 17.0f, 22.0f, '0');  
	la->setAnchorPoint(Point(0.5, 0.5));//原来的锚点在(0,0)  
	GTween::run(la,animal);

	result=(result>animal->getHP())?0:animal->getHP()-result;
	animal->setHP(result);
	return true;
}

void Skill::compele(BlockSprite* target)
{
	FightControl::getInstance()->getGrid()->removeBlock(target);
}
