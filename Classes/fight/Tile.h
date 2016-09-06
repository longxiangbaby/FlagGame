#ifndef  __TILE_H__
#define  __TILE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "TileData.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class Animal;
class TileData;

class GTile :public cocos2d::Node
{
public:
	GTile(void);
	~GTile(void);

	static GTile* create(); 

	bool init();

	/**
	* 获取邻居 ,默认返回自己
	* @param rdistance 行距
	* @param cdistance 列距
	* @return 
	* 
	*/
	GTile* getNeighbor(int rdistance,int cdistance);
	/**
	* 获取该tile下前方有怪的tile
	* @param direct 查找方向
	* @return 
	* 
	*/
	GTile* getNearExitAnimalTile(int direct);

	int getState();

	void setState(int val);

	void show(int index);

	void setGrid(GGrid* target);
	/**
	* 添加站立角色
	* @param Animal 怪物角色
	*/
	void addAnimal(Animal* target);
	/**
	* 移除站立角色
	*@param Animal 怪物角色
	*/
	void removeAnimal(Animal* target);
	
	Animal* getAnimal();

	TileData* getTileData();

private:
	CC_SYNTHESIZE(int,id,ID);
	CC_SYNTHESIZE(int,row,Row);
	CC_SYNTHESIZE(int,col,Col);

	Armature * p_armature;
	TileData* p_tileData;
	GGrid* p_grid;
	int state;
};

#endif