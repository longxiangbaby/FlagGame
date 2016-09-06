#include "BaseScene.h"


BaseScene::BaseScene(void)
{
}


BaseScene::~BaseScene(void)
{
}

void BaseScene::runScene()
{
	Scene* scene=Scene::create();
	scene->addChild(this);
	Director::getInstance()->replaceScene(scene);
}

void BaseScene::onEnter()
{
	Layer::onEnter();
}

void BaseScene::onExit()
{
	Layer::onExit();
}
