#ifndef __FIGHTSCENE_H__
#define __FIGHTSCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "animal/Animal.h"
#include "component/ChoiceBox.h"
#include "Scene/BaseScene.h"
#include "component/IconBox2.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;
using namespace cocostudio; 

class FightScene :public BaseScene
{
public:
	FightScene(void);
	~FightScene(void);

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(FightScene);

	void selectCallBack(Animal* animal);

	void updateUI();

	bool onChangeEvent(TouchEventType type,Item item,int id,string name);

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	virtual void update(float delta);

	virtual void onEnter();

	virtual void onExit();

	virtual void runScene();

private:
	ChoiceBox* choiceBox;
	ImageView* info_view;
	IconBox2* iconBox;
	ImageView* hp_bar;
	ImageView* mp_bar;
	Text* hp_txt;
	Text* mp_txt;
};
#endif
