#ifndef  __TILEDATA_H__
#define  __TILEDATA_H__
#include "game\Camp.h"
#include "animal\Animal.h"
#include "cocos2d.h"

USING_NS_CC;
class GTile;
class Animal;

class TileData:public Ref
{
public:
	TileData(void);
	~TileData(void);

	void addAnimal(Animal* animal);

	void removeAnimal(Animal* animal);

	//bool isBelongCamp(Camp* camp);

	bool isExitAnimal(Animal* animal);

	bool isEmpty(Animal* animal=nullptr);

	Animal* getAnimalIndex(int index);

	Vector<Animal*> getAnimals();

private:
	Vector<Animal*> animals;

};
#endif
