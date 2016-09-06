#ifndef  __UIMANAGER_H__
#define  __UIMANAGER_H__
#include "cocos2d.h"
#include <iostream>
#include "common\BaseLayer.h"

USING_NS_CC;
using namespace std;

class UIManager:public cocos2d::Ref
{
public:
	UIManager(void);
	~UIManager(void);

	static UIManager* getInstance();

	static void destroyInstance();

	virtual void addLayer(BaseLayer* baseLayer);

	virtual void removeLayer(BaseLayer* baseLayer);

	virtual void open(BaseLayer* baseLayer);

	virtual void close(BaseLayer* baseLayer);

	virtual bool isExist(string className);

	virtual Node* getPanel();

protected:
	Map<string,BaseLayer*> m_uis;

	Node* panel;

	BaseLayer* current;
};

#endif