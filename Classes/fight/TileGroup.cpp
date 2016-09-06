#include "TileGroup.h"
#include "Tile.h"
#include "animal\Animal.h"
#include "Global.h"

TileGroup::TileGroup(void)
{
	p_facus=nullptr;
	p_target=nullptr;

	setRC(1,1);
	vector<int> ver;
	ver.push_back(0);
	ver.push_back(0);
	datas.push_back(ver);
}

TileGroup::~TileGroup(void)
{
	datas.clear();
	p_facus=nullptr;
	p_tiles.clear();
	p_target=nullptr;
}

TileGroup* TileGroup::create(Animal* target)
{
	TileGroup* tileGroup=new TileGroup();
	tileGroup->setTarget(target);
	return tileGroup;
}

void TileGroup::setRC(int val1,int val2)
{
	row=val1;
	col=val2;
	size.width=row*64;
	size.height=col*64;
}

void TileGroup::setDatas(vector<vector<int>> vals)
{
	datas=vals;
	vector<int> ver;
	ver.push_back(0);
	ver.push_back(0);
	datas.push_back(ver);

	int maxRow=0;
	int minRow=0;

	int maxCol=0;
	int minCol=0;
	int size=datas.size();
	for (int i = 0; i < size; i++) 
	{
		if (maxRow<datas[i][1]) 
			maxRow=datas[i][1];
		if (minRow>datas[i][1]) 
			minRow=datas[i][1];

		if (maxCol<datas[i][0]) 
			maxCol=datas[i][0];
		if (minCol>datas[i][0]) 
			minCol=datas[i][0];
	}

	setRC(maxRow-minRow+1,maxCol-minCol+1);
}

vector<vector<int>> TileGroup::getDatas()
{
	return datas;
}

GTile* TileGroup::nextFocus(int direct,int step)
{
	return p_facus->getNeighbor(0,(direct==DIRECT_RIGHT)?step:-step);
}

GTile* TileGroup::getFocus()
{
	return p_facus;
}

void TileGroup::setFocus(GTile* tile)
{
	GTile* p_tile=nullptr;
	int length=datas.size();
	p_tiles.clear();

	for (int i = 0; i < length ; i++)
	{

		if (p_facus!=nullptr) 
		{
			p_tile=p_facus->getNeighbor(datas[i][0],datas[i][1]);
			if (p_tile)p_tile->removeAnimal(p_target);
		}

		if (!tile) return;

		p_tile=tile->getNeighbor(datas[i][0],datas[i][1]);
		if (p_tile!=nullptr){
			p_tile->addAnimal(p_target);
		}
		p_tiles.pushBack(p_tile);
	}
	p_facus=tile;
	ex=p_facus->getPositionX()+((int)size.width*(col-1)>>1);
	ey=p_facus->getPositionY()+((int)size.height/3);
}

bool TileGroup::isContainRow(int row)
{
	return true;
}

Vector<GTile*> TileGroup::getTiles()
{
	return p_tiles;
}

int TileGroup::getEx()
{
	return ex;
}

int TileGroup::getEy()
{
	return ey;
}

int TileGroup::getRow()
{
	return row;
}

int TileGroup::getCol()
{
	return col;
}

void TileGroup::show(bool isRecover)
{
	int length=datas.size();
	GTile* p_tile=nullptr;

	for (int i = 0; i < length ; i++)
	{
		if (p_facus!=nullptr) 
		{
			p_tile=p_facus->getNeighbor(datas[i][0],datas[i][1]);
			p_tile->show((isRecover)?p_tile->getState():1);
		}
	}

}

Map<int,GTile*> TileGroup::getRowTiles()
{
	Map<int,GTile*> m_tiles;
	int length=datas.size();
		for (int i = 0; i < length; i++) 
		{
			GTile* tile=p_facus->getNeighbor(datas[i][0],datas[i][1]);
			if (tile)m_tiles.insert(tile->getRow(),tile);
		}
	return m_tiles;
}
