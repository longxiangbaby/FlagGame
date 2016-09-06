#include "LoadingScene.h"
#include "global.h"


LoadingScene::LoadingScene(void)
{
	count=0;
	armatureIndex=0;
	spriteIndex=0;
	pvrIndex=0;
	total=0;
	sourceType=ARMATURE;
	isLoader=false;
}


LoadingScene::~LoadingScene(void)
{
	armaturePaths.clear();
	spritePaths.clear();
	complete=nullptr;
	CCLOG("LoadingScene is destroy!");
}

void LoadingScene::createScene()
{

}

bool LoadingScene::init()
{

	return true;
}


void LoadingScene::setSources(vector<string> paths,SourceType type)
{
	switch (type)
	{
	case ARMATURE:
		armaturePaths.insert(armaturePaths.end(),paths.begin(),paths.end());
		break;
	case SPRITE:
		spritePaths.insert(spritePaths.end(),paths.begin(),paths.end());
		break;
	case PVR:
		pvrPlists.insert(pvrPlists.end(),paths.begin(),paths.end());
		break;
	case MUSIC:

		break;
	default:
		break;
	}
	total+=paths.size();
}

void LoadingScene::startLoader()
{
	isLoader=true;
	this->scheduleUpdate();
	nextLoader(sourceType);
}
 

void LoadingScene::loadAnimationComplete(float time)
{
	int len=armaturePaths.size();
	if (armatureIndex>=len-1)
	{
		nextLoader(SPRITE);
	}
	armatureIndex++;
	isLoader=true;
}

void LoadingScene::loadSpriteCallBack(cocos2d::Texture2D *texture)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spritePaths[spriteIndex]+".plist",texture);
	CCLOG("path:%s",spritePaths[spriteIndex].c_str());
	int len=spritePaths.size();

	if (spriteIndex>=len-1)
		nextLoader(PVR);

	spriteIndex++;
	isLoader=true;
}

void LoadingScene::loadPVRCallBack(cocos2d::Texture2D *texture)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(pvrPlists[pvrIndex].append("plist"), texture);  

	pvrIndex++;  
	isLoader = true;  

	int len=pvrPlists.size();
	if (pvrIndex>=len-1)nextLoader(PVR);
	
}

void LoadingScene::onEnter()
{
	Layer::onEnter();

	//auto label = Label::createWithSystemFont("Loading................", FONT_NAME, FONT_SIZE);
	//this->addChild(label);
	//Color3B color(226, 121, 7);
	//label->setColor(color);
	//label->setPosition(300,300);

	Size visibleSize = Director::getInstance()->getWinSize();
	Sprite* loader=Sprite::createWithSpriteFrameName("loading.png");
	Size size=loader->getContentSize();
	loader->setPosition(visibleSize.width/2,(visibleSize.height-size.height)/2);
	this->addChild(loader,10);
}

void LoadingScene::onExit()
{
	Layer::onExit();
}

void LoadingScene::update(float delta)
{
	if (isLoader)
		onLoader(sourceType);
}

void LoadingScene::onLoader(SourceType index)
{
	isLoader=false;
	count++;
	switch (index)
	{
	case ARMATURE:
		ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(armaturePaths[armatureIndex]+".ExportJson",this,schedule_selector(LoadingScene::loadAnimationComplete));
		break;
	case SPRITE:
		TextureCache::getInstance()->addImageAsync(spritePaths[spriteIndex]+".png",CC_CALLBACK_1(LoadingScene::loadSpriteCallBack,this));
		break;
	case PVR:
		TextureCache::getInstance()->addImageAsync(pvrPlists[pvrIndex] + ".pvr.ccz",CC_CALLBACK_1(LoadingScene::loadPVRCallBack, this));  
		break;
	default:
		break;
	}

}

void LoadingScene::nextLoader(SourceType index)
{
	sourceType=index;
	if (count>=total-1)
	{
		if (complete)complete();
		this->unscheduleUpdate();
		armaturePaths.clear();
		spritePaths.clear();
		pvrPlists.clear();
		isLoader=false;
		return;
	}

	if (sourceType==ARMATURE&&armaturePaths.empty()){
		sourceType=SPRITE;
	}
	if (sourceType==SPRITE&&spritePaths.empty()){
		sourceType=PVR;
	}
	if (sourceType==PVR&&pvrPlists.empty()){
		//if (complete)complete();
		//this->unscheduleUpdate();
		//isLoader=false;
		//return;
	}
}



