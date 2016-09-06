#ifndef  __TILEGROUP_H__
#define  __TILEGROUP_H__
#include "cocos2d.h"
#include "Tile.h"
#include <iostream>
#include "animal\Animal.h"

USING_NS_CC;
using namespace std;

class GTile;
class Animal;

class TileGroup:public Ref
{
public:
	TileGroup(void);
	~TileGroup(void);

	static TileGroup* create(Animal* target);

	void setRC(int val1,int val2);

	void setDatas(vector<vector<int>> vals);

	void show(bool isRecover);

	vector<vector<int>> getDatas();

	GTile* nextFocus(int direct,int step);

	GTile* getFocus();

	void setFocus(GTile* tile);

	bool isContainRow(int row);

	Map<int,GTile*> getRowTiles();

	Vector<GTile*> getTiles();

	int getEx();
	int getEy();
	int getRow();
	int getCol();
private:
	int ex;
	int ey;
	int row;
	int col;
	Size size;
	vector<vector<int>> datas;
	GTile* p_facus;
	Vector<GTile*> p_tiles;
	CC_SYNTHESIZE(Animal*,p_target,Target);
};
#endif