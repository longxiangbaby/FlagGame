#include "CityVO.h"


CityVO::CityVO(void)
{

}

CityVO::~CityVO(void)
{

}


CVO CityVO::getPeople()
{
	return peo;
}

CVO CityVO::getMoneny()
{
	return money;
}

CVO CityVO::getBing()
{
	return bing;
}

CVO CityVO::getFood()
{
	return food;
}

CVO CityVO::getWood()
{
	return wood;
}

CVO CityVO::getIron()
{
	return iron;
}

CityVO* CityVO::create()
{
	return new CityVO();
}
