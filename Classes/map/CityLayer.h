#ifndef  __CITYLAYER_H__
#define  __CITYLAYER_H__
#include "common\BaseLayer.h"
#include "cocos2d.h"

USING_NS_CC;

class CityLayer:public BaseLayer
{
public:
	CityLayer(void);
	~CityLayer(void);

	CREATE_FUNC(CityLayer);

	virtual bool init();

};
#endif
