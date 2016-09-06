#ifndef  __TAVERNLAYER_H__
#define  __TAVERNLAYER_H__
#include "common\BaseLayer.h"


class TavernLayer:public BaseLayer
{
public:
	TavernLayer(void);
	~TavernLayer(void);

	virtual bool init();

};

#endif