#include "MapScene.h"
#include "ui/UIWidget.h"
#include "CocosGUI.h"
#include "MapLayer.h"
#include "MainScene.h"
#include "RoleLayer.h"
#include "control/GameControl.h"
#include "manager/UIManager.h"
#include "LMengLayer.h"
#include "RoomLayer.h"

using namespace ui;

MapScene::MapScene(void)
{

}

MapScene::~MapScene(void)
{

}

cocos2d::Scene* MapScene::createScene()
{
	auto scene=Scene::create();
	auto layer=MapScene::create();
	scene->addChild(scene);
	return scene;
}

bool MapScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Widget* mainui=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/MapUI.ExportJson");

	Layout* mapPanel=static_cast<Layout*>( Helper::seekWidgetByName(mainui, "MainPanel"));

	ImageView* map_veiw=static_cast<ImageView*>(mapPanel->getChildByName("map_veiw"));
	Button* role_btn=static_cast<Button*>(map_veiw->getChildByName("role_btn"));
	Button* lm_btn=static_cast<Button*>(map_veiw->getChildByName("lm_btn"));
	Button* xw_btn=static_cast<Button*>(map_veiw->getChildByName("xw_btn"));

	role_btn->addTouchEventListener(this,toucheventselector(MapScene::onTouchEvent));
	lm_btn->addTouchEventListener(this,toucheventselector(MapScene::onTouchEvent));
	xw_btn->addTouchEventListener(this,toucheventselector(MapScene::onTouchEvent));

	MapLayer* maplayer=MapLayer::createMap();

	this->addChild(maplayer);

	maplayer->loadMap("map/map.tmx");

	auto width = maplayer->getContentSize().width;
	auto height = maplayer->getContentSize().height;
	maplayer->runAction( MoveTo::create(1.0f, Point( -300, 0 ) ));

	this->addChild(mapPanel);
	this->addChild(UIManager::getInstance()->getPanel());
	return true;
}

void MapScene::onTouchEvent(Ref* pSender, TouchEventType type)
{
	Button* pbutton= static_cast<Button*>(pSender);

	string name=pbutton->getName();

	if (type==TOUCH_EVENT_ENDED)
	{
		if (name=="role_btn")
		{
			UIManager::getInstance()->open(RoleLayer::create());
		}
		if (name=="lm_btn")
		{
			UIManager::getInstance()->open(LMengLayer::create());
		}
		if (name=="xw_btn")
		{
			UIManager::getInstance()->open(RoomLayer::create());

		}

	}

}

void MapScene::onEnter()
{
	Layer::onEnter();
}

void MapScene::onExit()
{
	Layer::onExit();
	//Director::getInstance()->purgeCachedData();
}



