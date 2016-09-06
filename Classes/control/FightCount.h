#pragma once
#include "..\animal\Animal.h"
#include "..\skill\Skill.h"
class FightCount
{
public:
	FightCount(void);
	~FightCount(void);

	static void count(Animal* target, Skill* skill);


};

