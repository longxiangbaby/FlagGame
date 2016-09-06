#include "SkillVO.h"


SkillVO::SkillVO(void)
{
}


SkillVO::~SkillVO(void)
{
	v_areas.clear();
	CCLOG("SkillVO is destroy!");
}

ADDValue SkillVO::getAddValue() const
{
	return addValue;
}

void SkillVO::setAreas(vector< vector<int> > vals)
{
	v_areas=vals;
}

vector< vector<int> > SkillVO::getAreas()
{
	return v_areas;
}

HurtValue SkillVO::getHurtValue()
{
	return hurtType;
}
