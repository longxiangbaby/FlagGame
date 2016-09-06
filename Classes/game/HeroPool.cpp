#include "HeroPool.h"

static HeroPool* p_instance=nullptr;

HeroPool::HeroPool(void)
{

}


HeroPool::~HeroPool(void)
{
	heros.clear();
}

HeroPool* HeroPool::getInstance()
{
	if (p_instance==nullptr)
	{
		p_instance=new HeroPool();
	}
	return p_instance;
}

void HeroPool::destroy()
{
	CC_SAFE_DELETE(p_instance);
	p_instance=nullptr;
}

void HeroPool::addHero(Animal* animal)
{
	heros.insert(animal->getAnimalVO()->getID(),animal);
}

void HeroPool::removeHero(Animal* animal)
{
	heros.erase(animal->getAnimalVO()->getID());
}

Animal* HeroPool::getHero(int id)
{
	Animal* animal=heros.at(id);
	removeHero(animal);
	return animal;
}

Vector<Animal*> HeroPool::getRandoms(int size)
{
	Vector<Animal*> animals;

	for (int i = size - 1; i >= 0 ; i--)
	{
		animals.pushBack(heros.getRandomObject());
	}
	return animals;
}
