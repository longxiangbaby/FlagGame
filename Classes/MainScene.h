#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Scene/BaseScene.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio;
using namespace ui;

class MainScene : public BaseScene
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//virtual void onTouchEvent(TouchEventType type,Widget* target,int id,string name); 

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

	virtual void onTouchEvent(Ref* pSender, TouchEventType type); 

	virtual void onEnter();

	virtual void onExit();

	void loadCompele();

	void loadCompele2();


	virtual void runScene();

};

#endif // __HELLOWORLD_SCENE_H__
