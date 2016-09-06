#include "MainScene.h"
#include "map\MapScene.h"
#include "fight\FightScene.h"
#include "manager\ResourceDataManager.h"
#include "manager\GameDataManager.h"
#include "SimpleAudioEngine.h"
#include "global.h"
#include "Scene\LoadingScene.h"
#include "control\GameControl.h"
#include "control\FightControl.h"

USING_NS_CC;
using namespace cocostudio;

cocos2d::Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();
	//layer->autorelease();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Director::getInstance()->getTextureCache()->removeUnusedTextures();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	//GameDataManager::getInstance()->destroy();

	//auto* mapScene=MapScene::create();

	//this->addChild(mapScene);

	//Animal *animal=new Animal();
	//this->addChild(animal,2);
	return true;
}



void MainScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	cocostudio::ArmatureDataManager::destroyInstance();
	cocostudio::SceneReader::destroyInstance();
	cocostudio::GUIReader::destroyInstance();
	cocostudio::ActionManagerEx::destroyInstance();

	CCDirector::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::onEnter()
{
	Layer::onEnter();

	GameDataManager::getInstance()->loadXML();
	ResourceDataManager::getInstance()->loadAnimals();
	GameControl::getInstance()->init();

	Widget* mainui=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/MenuUI.ExportJson");
	Layout* menuPanel=static_cast<Layout*>( Helper::seekWidgetByName(mainui, "Panel_14"));
	this->addChild(menuPanel,5);	

	Button* start_btn=static_cast<Button*>(menuPanel->getChildByName("start_btn"));
	Button* read_btn=static_cast<Button*>(menuPanel->getChildByName("read_btn"));
	Button* ator_btn=static_cast<Button*>(menuPanel->getChildByName("ator_btn"));
	Button* exit_btn=static_cast<Button*>(menuPanel->getChildByName("exit_btn"));

	start_btn->addTouchEventListener(this,toucheventselector(MainScene::onTouchEvent));
	read_btn->addTouchEventListener(this,toucheventselector(MainScene::onTouchEvent));
	ator_btn->addTouchEventListener(this,toucheventselector(MainScene::onTouchEvent));
	exit_btn->addTouchEventListener(this,toucheventselector(MainScene::onTouchEvent));

	Node *pGameScene = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("publish/MainScene.json");
	this->addChild(pGameScene);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE,true);


}

void MainScene::onExit()
{
	Layer::onExit();
	//cocostudio::SceneReader::destroyInstance();
	//cocostudio::GUIReader::destroyInstance();

}

void MainScene::onTouchEvent(Ref* pSender, TouchEventType type)
{
		Button* pbutton= static_cast<Button*>(pSender);

		string name=pbutton->getName();

		if (type==TOUCH_EVENT_BEGAN)
		{
			//ActionManagerEx::getInstance()->releaseActions(); 

			if (name=="start_btn")
			{
				LoadingScene* loading=LoadingScene::create();
				loading->setSources(GameControl::getInstance()->getCamp(CAMP1)->getTeam(0)->getRolePaths(),ARMATURE);
				loading->setSources(GameControl::getInstance()->getPlayer()->getTeam(0)->getRolePaths(),ARMATURE);
				loading->setSources(GameControl::getInstance()->getPlayer()->getTeam(0)->getSkillPaths(),SPRITE);
				loading->setSources(GameControl::getInstance()->getCamp(CAMP1)->getTeam(0)->getSkillPaths(),SPRITE);
				loading->complete=CC_CALLBACK_0(MainScene::loadCompele,this);
				loading->runScene();
				loading->startLoader();

			}
			if (name=="read_btn")
			{
				ResourceDataManager::getInstance()->loadSources(CC_CALLBACK_0(MainScene::loadCompele2,this));

			}

		}
}

void MainScene::loadCompele()
{
	CCLOG("EEEEEEEEEEEEEEEEEEEend");
	//MapScene* map=MapScene::create();
	//map->runScene();	
	FightScene* fightScene=FightScene::create();
	fightScene->runScene();
}

void MainScene::loadCompele2()
{
	CCLOG("EEEEEEEEEEEEEEEEEEEend");
	MapScene* map=MapScene::create();
	map->runScene();	

}

void MainScene::runScene()
{
	Scene* scene=Scene::create();
	scene->addChild(this);
	Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.0f,scene));

	//Director::getInstance()->replaceScene(TransitionFadeDown::create(1.0f,scene));
}

