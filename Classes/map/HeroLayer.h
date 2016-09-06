#ifndef  __HEROLAYER_H__
#define  __HEROLAYER_H__
#include "common\BaseLayer.h"

class HeroLayer:public BaseLayer
{
public:
	HeroLayer(void);
	~HeroLayer(void);

	virtual bool init();

};
#endif
