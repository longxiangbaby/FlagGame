#ifndef  __CITYVO_H__
#define  __CITYVO_H__
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct CVO
{
	int o_value; //源值
	int o_max; //源上限
	int o_yield; //源产量

	int value; //值
	int max; //上限
	int yield; //产量
};

class CityVO:public cocos2d::Ref
{
public:
	CityVO(void);
	~CityVO(void);

	CityVO* create(); 

	CVO getPeople();
	CVO getMoneny();
	CVO getBing();
	CVO getFood();
	CVO getWood();
	CVO getIron();
private:
	CC_SYNTHESIZE(int,id,ID);
	CC_SYNTHESIZE(int,lv,Level);
	CC_SYNTHESIZE(string,name,Name);
	CVO peo;
	CVO money;
	CVO bing;
	CVO food;
	CVO wood;
	CVO iron;
};
#endif
