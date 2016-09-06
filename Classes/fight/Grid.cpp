#include "Grid.h"
#include "animal\AnimalSprite.h"
#include "cocostudio/CocoStudio.h"
#include "Tile.h"
#include "animal/Animal.h"
#include "control/FightControl.h"
#include "Global.h"

using namespace cocostudio;


GGrid::GGrid(void)
{
	role_layer=Layer::create();
	trap_layer=nullptr;
	p_tile=nullptr;
	p_animal=nullptr;
	p_mTile=nullptr;
	//CCLOG("GGrid is destroy!");
}

GGrid::~GGrid(void)
{
	m_rc.clear();

	for (int i=0;i < GRID_ROW;i++)
	{
		for (int j = 0; j < GRID_COL; j++)
		{
			p_tiles[i][j]=nullptr;
		}
	}
	_eventDispatcher->removeAllEventListeners();

	p_tile=nullptr;
	p_animal=nullptr;
	p_mTile=nullptr;
}


GGrid* GGrid::create()
{
	GGrid* grid=new GGrid();
	if (grid&& grid->init())
	{
		grid->autorelease();
	}else{
		CC_SAFE_DELETE(grid);
	}
	return grid;
}

bool GGrid::init()
{
	drawMap();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = CC_CALLBACK_2(GGrid::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GGrid::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GGrid::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void GGrid::drawMap()
{
	int index=0;
	for (int i=0;i < GRID_ROW;i++)
	{
		for (int j = 0; j < GRID_COL; j++)
		{
			GTile* tile=GTile::create();
			p_tiles[i][j]=tile;
			tile->setID(index);
			tile->setPosition(j*GRID_TILE_SIZE,i*GRID_TILE_SIZE);
			tile->setRow(i);
			tile->setCol(j);
			tile->setGrid(this);
			this->addChild(tile);
			index++;
		}
		index*=10;
	}

	this->addChild(role_layer);
}

void GGrid::put(GTile* tile)
{
	//CCLOG("XXXXXX:%d",tile->getRow());

	ArrayList<int> vec=m_rc.at(tile->getRow());

	if (vec.empty())
	{
		vec.pushBack(tile->getCol());
		m_rc.insert(tile->getRow(),vec);
	}else
	{
		m_rc.at(tile->getRow()).pushBack(tile->getCol());
	}
}

void GGrid::remove(GTile* tile)
{
	//CCLOG("TTTTT:%d",tile->getRow());
	m_rc.at(tile->getRow()).eraseObject(tile->getRow());
}

GTile* GGrid::findNear(GTile* tile,int direct)
{
	int min=10000;
	int result=0;
	ArrayList<int> cols=m_rc.at(tile->getRow());
	int length=cols.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		int num=cols.at(i);
		if (num==tile->getCol()) continue;
		int value=(direct==Direct::DIRECT_RIGHT)?num-tile->getCol():tile->getCol()-num;
		if( value < min&&value>0)
		{
			min = value;
			result = num;
		}
	}
	return getTile(tile->getRow(),result);
}

GTile * GGrid::getTileXY(int x,int y)
{
	return getTile(y>>6,x>>6);
}

GTile * GGrid::getTile(int row,int col)
{
	return (row>=GRID_ROW||row<0||col>=GRID_COL||col<0)?nullptr:p_tiles[row][col];
}

Size* GGrid::getTileSize()
{
	return NULL;
}


void GGrid::addAnimal(Animal* animal,GTile* tile,bool isAdd)
{
	AnimalSprite* va=animal->getAnimalSprite();
	animal->setStand(tile);
	int ex=animal->getStands()->getEx();
	int ey=animal->getStands()->getEy();
	va->setPosition(ex,ey);
	TileGroup* stands=animal->getStands();

	int depth=stands->getFocus()->getID();

	if (isAdd)
	{
		role_layer->addChild(va,1000-depth);
	}else{
		va->setLocalZOrder(1000-depth);
	}
}

void GGrid::removeAnimal(Animal* animal)
{
	role_layer->removeChild(animal->getAnimalSprite());
}

void GGrid::addEffctBlock(Node* node,Animal* target)
{
	GTile* tile=target->getFocus();
	float x=target->getAnimalSprite()->getPositionX();
	float y=target->getAnimalSprite()->getPositionY();
	node->setPosition(x,y);
	role_layer->addChild(node,1000-(tile->getID()-GRID_COL));
}

void GGrid::removeBlock(Node* node)
{
	role_layer->removeChild(node);
}


void GGrid::onEnter()
{
	Node::onEnter();
}

void GGrid::onExit()
{
	Node::onExit();
}

bool GGrid::onTouchBegan(Touch* touch, Event* event)
{
	if (FightControl::getInstance()->isTurn)return false;
	int localX=touch->getLocation().x-getPositionX()+32;
	int localY=touch->getLocation().y-getPositionY()+32;
	p_tile=getTileXY(localX,localY);

	Animal* sanimal=FightControl::getInstance()->getSelectAnimal();
	if (sanimal!=nullptr)
	{
		sanimal->showSkillArea(nullptr,true);
	}

	if (p_tile==nullptr)
	{
		CCLOG("Point X:%f,Y:%f",localX,localY);
	}else{
		p_animal=p_tile->getAnimal();
		if (p_animal==nullptr)
		{
			p_tile->show(1);
		}else
		{
			if (sanimal!=nullptr)
			{
				sanimal->getStands()->show(true);
			}
			p_animal->showSkillArea(p_tile,false);
			FightControl::getInstance()->selectAnimal(p_animal);
			if (p_animal->getCamp()->getFlag()!=PLAYER){
				p_tile=nullptr;
				p_animal=nullptr;
			}
		}

	}
	return true;
}

void GGrid::onTouchMoved(Touch* touch, Event* event)
{
	if (p_animal!=nullptr)
	{	
		p_animal->showSkillArea(p_tile,true);

		if (p_animal->getCamp()->getFlag()!=PLAYER){
			p_animal=nullptr;
			return;
		}

		p_animal->getAnimalSprite()->setLocalZOrder(1000);
		int localX=touch->getLocation().x-getPositionX();
		int localY=touch->getLocation().y-getPositionY();

		GTile* t_tile=getTileXY(localX+32,localY+32);
		
		if (t_tile==p_mTile)
		{
			p_animal->showSkillArea(p_mTile,false);
		}else
		{
			p_animal->showSkillArea(p_mTile,true);
			if (p_mTile!=nullptr)
			{
				if (p_mTile!=p_tile)
				{
					p_mTile->show(p_mTile->getState());
				}
			}

			if (t_tile!=nullptr)
			{
				t_tile->show(1);
				p_animal->showSkillArea(t_tile,false);
			}
			p_mTile=t_tile;

		}
		p_animal->getAnimalSprite()->setPosition(Point(localX,localY));
	}
	
}

void GGrid::onTouchEnded(Touch* touch, Event* event)
{
	if (p_tile==nullptr)return;

	p_tile->show(p_tile->getState());

	if (p_animal==nullptr){
		p_tile=nullptr;
		return;
	}

	int localX=touch->getLocation().x-getPositionX()+32;
	int localY=touch->getLocation().y-getPositionY()+32;
	p_tile=getTileXY(localX,localY);
	if (p_tile==nullptr)
	{
		addAnimal(p_animal,p_animal->getStands()->getFocus(),false);
	}else{
		Animal* taget=p_tile->getAnimal();

		if (p_tile->getState()!=p_animal->getCamp()->getState())
		{
			addAnimal(p_animal,p_animal->getStands()->getFocus(),false);
			if (taget!=nullptr)taget->getStands()->show(true);
			FightControl::getInstance()->getSelectAnimal()->showSkillArea(p_tile,true);
		}else{
			if (taget!=nullptr)
			{
				addAnimal(taget,p_animal->getStands()->getFocus(),false);
				addAnimal(p_animal,p_tile,false);
			}else
			{
				addAnimal(p_animal,p_tile,false);
			}
		}
		FightControl::getInstance()->getSelectAnimal()->getStands()->show(false);
		FightControl::getInstance()->getSelectAnimal()->showSkillArea(nullptr,false);

	}
	p_animal=nullptr;
	p_tile=nullptr;
}

void GGrid::setStateToCol(int col,int state,int direct)
{
	switch (direct)
	{
	case DIRECT_UP:
		break;
	case DIRECT_RIGHT:
		for (int r = 0; r < GRID_ROW ; r++)
		{
			for (int c = 0; c < col ; c++)
			{
				p_tiles[r][c]->setState(state);
			}
		}
		break;
	case DIRECT_LEFT:
		for (int r = 0; r < GRID_ROW ; r++)
		{
			for (int c = GRID_COL-1; c >= col ; c--)
			{
				p_tiles[r][c]->setState(state);
			}
		}
		break;
	case DIRECT_DOWN:
		break;
	default:
		break;
	}
}

void GGrid::destroy()
{

}


