#ifndef  __CITYVO_H__
#define  __CITYVO_H__
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct CVO
{
	int o_value; //Դֵ
	int o_max; //Դ����
	int o_yield; //Դ����

	int value; //ֵ
	int max; //����
	int yield; //����
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
