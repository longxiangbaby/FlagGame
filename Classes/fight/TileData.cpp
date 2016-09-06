#include "TileData.h"
#include "util\ArrayUtil.h"

TileData::TileData(void)
{
}


TileData::~TileData(void)
{
	animals.clear();
}

void TileData::addAnimal(Animal* animal)
{
	animals.pushBack(animal);
}

void TileData::removeAnimal(Animal* animal)
{
	animals.eraseObject(animal);
}

//bool TileData::isBelongCamp(Camp* camp)
//{
//	return true;
//}

bool TileData::isExitAnimal(Animal* animal)
{
	return true;
}

bool TileData::isEmpty(Animal* animal/*=nullptr*/)
{
	if (animals.size()!=0) 
	{
		if (animals.at(0) == animal||animals.at(0)->isDead) 
			return true;
	}
	return (animals.size()==0)?true:false;
}

Animal* TileData::getAnimalIndex(int index)
{
	if (animals.empty())
	{
		return nullptr;
	}
	return animals.at(index);
}

Vector<Animal*> TileData::getAnimals()
{
	return animals;
}
