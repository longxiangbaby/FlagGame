#ifndef __GGRID_H__
#define __GGRID_H__

#include "cocos2d.h"
#include "animal/Animal.h"
#include "Tile.h"
#include "game/Camp.h"
#include "util/HashMap.h"
#include "util/ArrayList.h"

#ifndef GRID_ROW
#define GRID_ROW 4
#endif
#ifndef GRID_COL
#define GRID_COL 20
#endif
#ifndef GRID_TILE_SIZE
#define GRID_TILE_SIZE 64
#endif

USING_NS_CC;
using namespace ui;

class GTile;

class GGrid :public cocos2d::Node
{
public:
	GGrid(void);
	~GGrid(void);

	static GGrid* create();

	bool init();

	void drawMap();

	void destroy();

	void put(GTile* tile);

	void remove(GTile* tile);

	void setStateToCol(int col,int state,int direct);

	GTile* findNear(GTile* tile,int direct);

	GTile* getTileXY(int x,int y);

	GTile* getTile(int row,int col);

	Size* getTileSize();
	/*
	 添加怪到指定格子
	 @isAdd 如果为false，不添加，只调整位置
	*/
	void addAnimal(Animal* animal,GTile* tile,bool isAdd=true);

	void removeAnimal(Animal* animal);

	void addEffctBlock(Node* node,Animal* target);

	void removeBlock(Node* node);

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchMoved(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	virtual void onEnter();

	virtual void onExit();

private:
	GTile* p_tiles[GRID_ROW][GRID_COL];
	HashMap<int,ArrayList<int>> m_rc;
	Node* role_layer;
	Node* trap_layer;

	GTile* p_tile;
	Animal* p_animal;
	GTile* p_mTile;
};
#endif 