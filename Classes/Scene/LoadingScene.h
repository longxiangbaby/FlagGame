#ifndef  __LOADINGSCENE_H__
#define  __LOADINGSCENE_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <iostream>
#include "ui/UIWidget.h"
#include "CocosGUI.h"
#include "BaseScene.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio;

typedef enum {
	ARMATURE,
	SPRITE,
	PVR,
	MUSIC
} SourceType;

class LoadingScene:public BaseScene
{
public:
	LoadingScene(void);
	~LoadingScene(void);

	void createScene();

	virtual bool init();  

	CREATE_FUNC(LoadingScene);

	void loadSpriteCallBack(cocos2d::Texture2D *texture);//异步加载完成后回调主程序的函数  

	void loadAnimationComplete(float time);//异步加载完成后回调主程序的函数  

	void loadPVRCallBack(cocos2d::Texture2D *texture);//异步加载完成后回调主程序的函数  

	void setSources(vector<string> paths,SourceType type);

	void startLoader();

	void onLoader(SourceType index);

	void nextLoader(SourceType index);

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float delta);

public:
	std::function<void()>complete;
private:
	int total,count,armatureIndex,spriteIndex,pvrIndex;
	SourceType sourceType;
	vector<string> armaturePaths;
	vector<string> spritePaths;
	vector<string> pvrPlists;
	bool isLoader;

};
#endif

