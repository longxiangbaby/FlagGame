#ifndef  __HEROPOOL_H__
#define  __HEROPOOL_H__
#include "cocos2d.h"
#include "animal\Animal.h"

USING_NS_CC;

//Ó¢ÐÛ³Ø,
class HeroPool:public cocos2d::Ref
{
public:
	HeroPool(void);
	~HeroPool(void);

	static HeroPool* getInstance();

	static void destroy();

	void addHero(Animal* animal);

	void removeHero(Animal* animal);

	Animal* getHero(int id);

	Vector<Animal*> getRandoms(int size);

protected:
	Map<int,Animal*> heros;

};
#endif
