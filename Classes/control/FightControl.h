#ifndef  __FIGHT_CONTROL_H__
#define  __FIGHT_CONTROL_H__

#include "animal\Team.h"
#include "fight\Grid.h"
#include "fight\Tile.h"
#include "cocos2d.h"
#include "animal\Animal.h"
#include <iostream>
#include "GTween.h"

using namespace std;
USING_NS_CC;

class FightControl:public Ref
{
public:
	FightControl(void);
	~FightControl(void);

	static FightControl* getInstance();

	void init();

	void pause();

	void recall(int round);

	void update(float delta);

	void nextRound();

	void onTurn();

	void onTrap();

	void onSkill();

	void onMove();

	void roundDown();

	void selectAnimal(Animal* animal);

	void removeAnimal(Animal* animal);

	Animal* getSelectAnimal();

	void setGrid(GGrid* grid);

	GGrid* getGrid();

	void destroy();
protected:
	void call(Animal* animal,GTile* tile);

	void sortOn();

	void countFight();

public:
	std::function<void(Animal*)> selectCall;
	bool isTurn;
private:
	Team* p_teamOne;
	Team* p_teamTwo;
	GGrid* p_grid;
	Animal* select;//选中的角色
	Animal* p_animal;//当前释放技能角色
	Animal* last;//最后一个移动完毕
	Vector<Animal*> animals;
	Vector<Animal*> fights;
	Vector<Animal*> deads;
	int round;
	int turn;
};

class CompereToMove  
{  
public:  
	bool operator ()(const Animal* child1, const Animal* child2)  
	{  
		return (child1->getSort()>child2->getSort())?true:false; 
	}  
};  
class CompereToSpeed  
{  
public:  
	bool operator ()(const Animal* child1, const Animal* child2)  
	{  
		return (child1->getSpeed()>child2->getSpeed())?true:false; 
	}  
};  

#endif // !1
