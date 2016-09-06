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
	* ��ȡ�ھ� ,Ĭ�Ϸ����Լ�
	* @param rdistance �о�
	* @param cdistance �о�
	* @return 
	* 
	*/
	GTile* getNeighbor(int rdistance,int cdistance);
	/**
	* ��ȡ��tile��ǰ���йֵ�tile
	* @param direct ���ҷ���
	* @return 
	* 
	*/
	GTile* getNearExitAnimalTile(int direct);

	int getState();

	void setState(int val);

	void show(int index);

	void setGrid(GGrid* target);
	/**
	* ���վ����ɫ
	* @param Animal �����ɫ
	*/
	void addAnimal(Animal* target);
	/**
	* �Ƴ�վ����ɫ
	*@param Animal �����ɫ
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