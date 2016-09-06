#include "Tile.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
#include "CocosGUI.h"
#include "TileData.h"
#include "Grid.h"
#include "global.h"

using namespace ui;
using namespace cocostudio; 
USING_NS_CC;


GTile::GTile(void)
{
	p_grid=nullptr;
	p_armature=nullptr;
}

GTile::~GTile(void)
{
	CC_SAFE_DELETE(p_tileData);
	p_grid=nullptr;
	p_armature=nullptr;
	//CCLOG("GTile is destroy!");
}

GTile* GTile::create()
{
	GTile* tile=new GTile();
	if (tile&&tile->init())
	{
		tile->autorelease();
	}else
	{
		CC_SAFE_DELETE(tile);
	}
	return tile;
}


GTile* GTile::getNeighbor(int rdistance,int cdistance)
{
	return p_grid->getTile(row+rdistance,col+cdistance);
}

GTile* GTile::getNearExitAnimalTile(int direct)
{
	return p_grid->findNear(this,direct);
}

bool GTile::init()
{
	p_tileData=new TileData();
	p_armature = Armature::create("Tile");
	addChild(p_armature);
	this->setState(0);
	return true;
}

int GTile::getState()
{
	return state;
}

void GTile::setState(int val)
{
	state=val;
	show(val);
}

void GTile::show(int index)
{
	p_armature->getAnimation()->playWithIndex(0);
	p_armature->getAnimation()->gotoAndPause(index);
}

void GTile::addAnimal(Animal* target)
{
	p_tileData->addAnimal(target);
	setState(target->getCamp()->getState());
	p_grid->put(this);
}

void GTile::removeAnimal(Animal* target)
{
	p_tileData->removeAnimal(target);
	p_grid->remove(this);
}

void GTile::setGrid(GGrid* target)
{
	p_grid=target;
}


Animal* GTile::getAnimal()
{
	return p_tileData->getAnimalIndex(0);
}

TileData* GTile::getTileData()
{
	return p_tileData;
}





