#include "ResourceDataManager.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIWidget.h"
#include "CocosGUI.h"
#include "Scene/LoadingScene.h"

using namespace cocostudio; 
USING_NS_CC;

static ResourceDataManager* p_resourceDataManager=nullptr;


ResourceDataManager::ResourceDataManager(void)
{

}


ResourceDataManager::~ResourceDataManager(void)
{

}

ResourceDataManager* ResourceDataManager::getInstance()
{
	if (p_resourceDataManager==nullptr)
	{
		p_resourceDataManager=new ResourceDataManager();
		//if (p_resourceDataManager && p_resourceDataManager->init())
		//{
		//	//p_resourceDataManager->autorelease();
		//}else{
		//	CC_SAFE_DELETE(p_resourceDataManager);
		//}
	}
	return p_resourceDataManager;
}

bool ResourceDataManager::init()
{
	return true;
}

bool ResourceDataManager::loadAnimals()
{
	ArmatureDataManager* admanager=ArmatureDataManager::getInstance();

	SpriteFrameCache* framecache=SpriteFrameCache::getInstance();
	framecache->addSpriteFramesWithFile("image/source.plist","image/source.png");

	framecache->addSpriteFramesWithFile("icon/heroIcon1.plist","icon/heroIcon1.png");
	framecache->addSpriteFramesWithFile("icon/heroIcon2.plist","icon/heroIcon2.png");


	admanager->addArmatureFileInfo("publish/Tile0.png","publish/Tile0.plist","publish/Tile.ExportJson");
	admanager->addArmatureFileInfo("map/city0.png","map/city0.plist","map/city.ExportJson");
	admanager->addArmatureFileInfo("icon/SkillIcon0.png","icon/SkillIcon0.plist","icon/SkillIcon.ExportJson");
	admanager->addArmatureFileInfo("icon/HeroIcon0.png","icon/HeroIcon0.plist","icon/HeroIcon.ExportJson");

	return true;
}

void ResourceDataManager::destroyInstance()
{
	delete p_resourceDataManager;
	p_resourceDataManager=nullptr;
}


bool ResourceDataManager::loadSources(const std::function<void()>& callback)
{
	ArmatureDataManager* admanager=ArmatureDataManager::getInstance();

	SpriteFrameCache* framecache=SpriteFrameCache::getInstance();
	framecache->addSpriteFramesWithFile("image/source.plist","image/source.png");

	vector<string> path1;
	path1.push_back("icon/heroIcon1");
	path1.push_back("icon/heroIcon2");

	vector<string> path;
	path.push_back("publish/Tile");
	path.push_back("map/city");
	path.push_back("icon/SkillIcon");
	path.push_back("icon/HeroIcon");

	LoadingScene* loading=LoadingScene::create();
	loading->setSources(path,ARMATURE);
	loading->setSources(path1,SPRITE);
	loading->complete=callback;
	loading->runScene();
	loading->startLoader();


	return true;
}

bool ResourceDataManager::loadRole(string name)
{
	ArmatureDataManager* admanager=ArmatureDataManager::getInstance();
	string path=name+"/"+name;
	admanager->addArmatureFileInfo("Role/"+path+"0.png","Role/"+path+"0.plist","Role/"+path+".ExportJson");
	return true;
}

bool ResourceDataManager::loadSkill(string name)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("skill/"+name+".plist","skill/"+name+".png");

	return true;
}

bool ResourceDataManager::removeRole(string name)
{	
	return true;
}

bool ResourceDataManager::removeRoles(vector<string> names)
{
	ArmatureDataManager* admanager=ArmatureDataManager::getInstance();

	int length=names.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		string path="Role/"+names[i]+"/"+names[i]+".ExportJson";
		admanager->removeArmatureFileInfo(path);
	}
	return true;
}

bool ResourceDataManager::removeSkills(vector<string> skills)
{
	int length=skills.size();
	for (int i = length - 1; i >= 0 ; i--)
	{
		string path="skill/"+skills[i]+".plist";
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(path);
	}
	return true;

}



