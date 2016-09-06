#include "Animal.h"
#include <iostream>
#include "cocostudio\CocoStudio.h"
#include "Global.h"
#include "manager\ResourceDataManager.h"
#include "SimpleAudioEngine.h"
#include "manager\GameDataManager.h"

using namespace cocostudio;
using namespace std;

void Animal::onExit()
{

}

void Animal::onEnter()
{
	//ResourceDataManager::getInstance()->loadRole(p_animalVO->getPath());
	//size = CCDirector::sharedDirector()->getVisibleSize();
	////2048*1536

	//size.height = 1536;
	//size.width = 2048;

	//Armature* armature = Armature::create("CLXiang");
	//armature->getAnimation()->playByIndex(4);
	//armature->getAnimation()->gotoAndPause(4);
	//armature->setPosition(ccp(500,300));
}

Animal::Animal(void):direct(DIRECT_RIGHT),
	p_animalVO(nullptr),
	p_camp(nullptr),
	p_skill(nullptr),
	p_vanimal(nullptr),
	isDead(false),
	sort(0),
	isTurnEnd(true),
	step(1),
	hp(0),
	mp(0)
{
	p_stands=TileGroup::create(this);
}

Animal::~Animal(void)
{
	CC_SAFE_DELETE(p_animalVO);
	CC_SAFE_DELETE(p_stands);
	CC_SAFE_DELETE(p_skill);
	p_camp=nullptr;
	p_vanimal=nullptr;
	CCLOG("Animal is destroy!");
}

Animal* Animal::create()
{
	Animal* animal=new Animal();
	if (animal&&animal->init())
	{	
		//animal->autorelease();
	}else
	{
		CC_SAFE_DELETE(animal);
	}
	return animal;
}

bool Animal::init()
{
	return true;
}

AnimalVO* Animal::getAnimalVO()
{
	return p_animalVO;
}

void Animal::setAnimalVO(AnimalVO* val)
{
	p_animalVO=val;
	onEnter();
	setHP(p_animalVO->getMaxLife());
	setMP(p_animalVO->getMp());

}

AnimalSprite* Animal::getAnimalSprite()
{
	if (p_vanimal==nullptr)
	{
		Armature* armature = Armature::create(p_animalVO->getPath());
		p_vanimal=AnimalSprite::create(armature,getHP());
		p_vanimal->actionEvent=CC_CALLBACK_3(Animal::onActionEvent,this);
		p_vanimal->frameEvent=CC_CALLBACK_4(Animal::onFrameEvent,this);
	}
	int scale=(direct==DIRECT_RIGHT)?1:-1;
	p_vanimal->setFace(scale);
	onWait();
	return p_vanimal;
}

void Animal::update()
{
	
}

void Animal::onAction(string actinName,bool isWait)
{
	isTurnEnd=false;
	p_vanimal->play(actinName,isWait);
}

void Animal::onSkill()
{
	if (p_skill!=nullptr){
		if (isAttack()) 
		{
			onAction(StringUtil::StringAddInt("skill",p_skill->getSkillVO()->getAction()),false);
		}
	}
}

void Animal::onWait()
{
	isTurnEnd=true;
	p_vanimal->play("wait",true);
}

bool Animal::onMove()
{
	p_stands->show(true);
	p_skill->show(getFocus(),true);//技能范围砖块效果复位
	vector<GTile*> next;
	int i=1;
	while(i<=step){
		GTile* nextTile=isSteps(i);
		if (nextTile) 
			next.push_back(nextTile);
		else
			break;
		i++;
	}
	int len=next.size();
	if (len==0) return false;	
	for (int i = len - 1; i >= 0 ; i--){setStand(next[i]);}
	
	onAction("run",true);
	GTween::to(p_vanimal,p_stands->getEx(),p_stands->getEy(),
		(direct==Direct::DIRECT_LEFT)?-8:8,CC_CALLBACK_0(Animal::onWait,this));
	this->sort=0;
	next.clear();
	return true;
}

GTile* Animal::isSteps(int step)
{
	GTile* nextTile=p_stands->nextFocus(direct,step);

	if (!nextTile) return nullptr;
	int len=p_stands->getDatas().size();
	for (int i = 0; i < len; i++) 
	{
		GTile* tile=nextTile->getNeighbor(p_stands->getDatas()[i][0],p_stands->getDatas()[i][1]);
		if (!tile->getTileData()->isEmpty(this)) return nullptr;
	}
	return (nextTile->getTileData()->isEmpty(this))?nextTile:nullptr;
}

void Animal::setDirect(int val)
{
	if (direct==val)return;
	direct=val;
}

void Animal::swichSkill(int index)
{
	p_skill=getSkill(index);
	skillIndex=index;
}

void Animal::addSkill(Skill* val,int index)
{
	m_skills.insert(index,val);
}

Skill* Animal::getSkill(int index)
{
	return m_skills.at(index);
}

Skill* Animal::getSelectSkill()
{
	return p_skill;
}

int Animal::getSelectSkillIndex()
{
	return skillIndex;
}

void Animal::setStand(GTile* tile)
{
	p_stands->setFocus(tile);
}

TileGroup* Animal::getStands()
{
	return p_stands;
}


Camp* Animal::getCamp()
{
	return p_camp;
}

void Animal::setCamp(Camp* camp)
{
	p_camp=camp;
}

void Animal::showSkillArea(GTile* tile,bool isRestore)
{
	if (p_skill!=nullptr)
	{
		p_skill->show((tile==nullptr)?p_stands->getFocus():tile,isRestore);
	}
}

int Animal::getDirect()
{
	return direct;
}

int Animal::getSkillSize()
{
	return m_skills.size();
}

SkillVO* Animal::getSkillVO(int index)
{
	Skill* skill=getSkill(index);
	return (skill==nullptr)?nullptr:skill->getSkillVO();
}

GTile* Animal::getFocus()
{
	return p_stands->getFocus();
}

void Animal::onActionEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	switch (movementType)
	{
	case cocostudio::START:
		break;
	case cocostudio::COMPLETE:
		break;
	case cocostudio::LOOP_COMPLETE:
		onWait();
		break;
	default:
		break;
	}
}

void Animal::onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex)
{
	if (evt=="hit")
	{
		CCLOG("hitXXXXXXXXXXXXXXXXXXXx!");
		p_skill->execute();

	}
}

vector<string> Animal::getSkillPaths()
{
	vector<string> paths;
	int len=m_skills.size();
	for (int i = len - 1; i >= 0 ; i--)
	{
		paths.push_back(getSkillVO(i)->getPath());
	}
	return paths;
}

std::string Animal::getRace()
{
	string raceName="";
	switch (p_animalVO->getRace()-1)
	{
	case Race::SOLDIERS:
		raceName=GameDataManager::getText("soldiers");
		break;
	case Race::ARCHERS:
		raceName=GameDataManager::getText("archers");
		break;
	case Race::MAGE:
		raceName=GameDataManager::getText("mage");
		break;
	default:
		break;
	}
	return raceName;
}

bool Animal::isAttack()
{
	return p_skill->isExist();
}

void Animal::setSelectSkillIndex(int index)
{
	p_skill=getSkill(index);
}

int Animal::getSpeed() const
{
	return p_animalVO->getSpeed();
}

void Animal::setHP(int curhp)
{
	hp=curhp;
	if (p_vanimal)p_vanimal->setCurValue(hp);
}

int Animal::getHP()
{
	return hp;
}

void Animal::setMP(int curmp)
{
	mp=curmp;
}

int Animal::getMP()
{
	return mp;
}

bool Animal::onDead()
{
	return true;
}



