#include "FightScene.h"
#include "cocostudio/CocoStudio.h"
#include "Grid.h"
#include "manager/GameDataManager.h"
#include "game/Camp.h"
#include "game/Player.h"
#include "animal/Team.h"
#include "control/FightControl.h"
#include "Global.h"
#include "component/ChoiceBox.h"
#include "skill/SkillVO.h"
#include "manager/ResourceDataManager.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "control/GameControl.h"
#include "util/StringUtil.h"

FightScene::FightScene(void):
	iconBox(nullptr)
{

}

FightScene::~FightScene(void)
{
	choiceBox=nullptr;
	CCLOG("FightScene is destroy!");
}

Scene* FightScene::createScene()
{
	auto scene=Scene::create();
	auto layer=FightScene::create();
	scene->addChild(scene);
	return scene;
}

bool FightScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Node *pGameScene = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("publish/FightScene.json");
	this->addChild(pGameScene);

	Widget* mainui=cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/FightUI.ExportJson");
	Layout* fightPanel=static_cast<Layout*>( Helper::seekWidgetByName(mainui, "Fight_Panel"));
	info_view=static_cast<ImageView*>(fightPanel->getChildByName("info_view"));
	Button* go_btn=static_cast<Button*>(info_view->getChildByName("go_btn"));
	go_btn->addTouchEventListener(this,toucheventselector(MainScene::onTouchEvent));

	fightPanel->setTouchEnabled(false);
	this->addChild(fightPanel,2);

	choiceBox=ChoiceBox::createChoiceBox(SKILL_ICON);
	Widget* items[5]={info_view->getChildByName("skill_0"),
		info_view->getChildByName("skill_1"),
		info_view->getChildByName("skill_2"),
		info_view->getChildByName("skill_3"),
		info_view->getChildByName("skill_4")};
	choiceBox->setComponents(items,5);
	choiceBox->onChangeEvent=CC_CALLBACK_4(FightScene::onChangeEvent,this);
	this->addChild(choiceBox);

	iconBox=IconBox2::createBox(ROLE_BIG_ICON);
	iconBox->setPosition(info_view->getSize().width/2,info_view->getSize().height/2);
	info_view->addChild(iconBox);

	FightControl* fc=FightControl::getInstance();
	fc->selectCall=CC_CALLBACK_1(FightScene::selectCallBack,this);
	this->addChild(fc->getGrid(),1);
	fc->init();

	return true;
}

void FightScene::onEnter()
{
	Layer::onEnter();

	this->scheduleUpdate();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FIGHT,true);
}

void FightScene::onExit()
{
	Layer::onExit();
	this->unscheduleUpdate();
	cocostudio::SceneReader::destroyInstance();
	cocostudio::GUIReader::destroyInstance();
}


void FightScene::selectCallBack(Animal* animal)
{
	Icon* skills[4]={animal->getSkillVO(0),
		animal->getSkillVO(1),
		animal->getSkillVO(2),		
		animal->getSkillVO(3)};
	choiceBox->provide(skills,4);
	choiceBox->setSelectIndex(animal->getSelectSkillIndex());
	updateUI();
}

bool FightScene::onChangeEvent(TouchEventType type,Item item,int id,string name)
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		if (FightControl::getInstance()->isTurn)return false;
		Animal* animal=FightControl::getInstance()->getSelectAnimal();
		if (item.data==nullptr||animal->getCamp()->getFlag()!=PLAYER)return false;

		if (animal!=nullptr)
		{
			animal->showSkillArea(animal->getFocus(),true);
			animal->swichSkill(id);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MUSIC_SELECT,false);
			animal->showSkillArea(animal->getFocus(),false);
		}
	}if (type == TOUCH_EVENT_ENDED)
	{

	}
	return true;
}

void FightScene::update(float delta)
{
	FightControl::getInstance()->update(delta);
	Animal* animal=FightControl::getInstance()->getSelectAnimal();

	if (hp_bar)
	{
		hp_bar->setScaleX((float)animal->getHP()/animal->getAnimalVO()->getMaxLife());
		hp_txt->setText(StringUtil::m_toStr(animal->getHP())+"/"+StringUtil::m_toStr(animal->getAnimalVO()->getMaxLife()));
	}
	if (mp_bar)
	{
		mp_bar->setScaleX((float)animal->getMP()/animal->getAnimalVO()->getMp());
		mp_txt->setText(StringUtil::m_toStr(animal->getMP())+"/"+StringUtil::m_toStr(animal->getAnimalVO()->getMp()));
	}
}

void FightScene::onTouchEvent(Ref* pSender, TouchEventType type)
{
	Button* pbutton= static_cast<Button*>(pSender);

	string name=pbutton->getName();

	if (type==TOUCH_EVENT_BEGAN)
	{
		if (name=="go_btn")
		{
			//GameControl::getInstance()->destroy();
			//FightControl::getInstance()->destroy();
			//GameDataManager::getInstance()->destroy();
			//AnimationCache::getInstance()->destroyInstance();
			//ArmatureDataManager::getInstance()->destroyInstance();
			//Director::getInstance()->purgeCachedData();	
			//this->removeAllChildrenWithCleanup(true);

			//MainScene* scene = MainScene::create();
			//scene->runScene();
			FightControl::getInstance()->nextRound();
		}
	}
}

void FightScene::runScene()
{
	Scene* scene=Scene::create();
	scene->addChild(this);
	Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.0f,scene));
}

void FightScene::updateUI()
{
	Animal* animal=FightControl::getInstance()->getSelectAnimal();
	iconBox->setIndex(animal->getAnimalVO()->getIcon());
	Text* name_txt=static_cast<Text*>(info_view->getChildByName("name_txt"));
	name_txt->setText(animal->getAnimalVO()->getName());

	Text* lv_txt=static_cast<Text*>(info_view->getChildByName("lv")->getChildByName("txt"));
	lv_txt->setText(StringUtil::m_toStr(animal->getAnimalVO()->getLevel()));

	Text* race_txt=static_cast<Text*>(info_view->getChildByName("race_txt")->getChildByName("txt"));
	race_txt->setText(animal->getRace());

	hp_txt=static_cast<Text*>(info_view->getChildByName("hp_bar")->getChildByName("txt"));
	hp_txt->setText(StringUtil::m_toStr(animal->getHP())+"/"+StringUtil::m_toStr(animal->getAnimalVO()->getMaxLife()));
	hp_bar=static_cast<ImageView*>(info_view->getChildByName("hp_bar")->getChildByName("bar"));
	hp_bar->setScaleX((float)animal->getHP()/animal->getAnimalVO()->getMaxLife());

	mp_txt=static_cast<Text*>(info_view->getChildByName("mp_bar")->getChildByName("txt"));
	mp_txt->setText(StringUtil::m_toStr(animal->getMP())+"/"+StringUtil::m_toStr(animal->getAnimalVO()->getMp()));
	mp_bar=static_cast<ImageView*>(info_view->getChildByName("mp_bar")->getChildByName("bar"));
	mp_bar->setScaleX((float)animal->getMP()/animal->getAnimalVO()->getMp());
}

