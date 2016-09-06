#include "UIManager.h"

static UIManager* p_ui=nullptr;

UIManager::UIManager(void):current(nullptr)
{
	panel=Node::create();
}


UIManager::~UIManager(void)
{
	panel=nullptr;
	m_uis.clear();
}

void UIManager::addLayer(BaseLayer* baseLayer)
{
	m_uis.insert(baseLayer->panelName,baseLayer);
	panel->addChild(baseLayer);
}

void UIManager::removeLayer(BaseLayer* baseLayer)
{
	m_uis.erase(baseLayer->panelName);
	panel->removeChild(baseLayer);
}

void UIManager::open(BaseLayer* baseLayer)
{
	addLayer(baseLayer);
	baseLayer->open();
}

void UIManager::close(BaseLayer* baseLayer)
{
	removeLayer(baseLayer);
}

bool UIManager::isExist(string className)
{
	return (m_uis.at(className))?true:false;
}

Node* UIManager::getPanel()
{
	return panel;
}

UIManager* UIManager::getInstance()
{
	if (p_ui==nullptr)
	{
		p_ui=new UIManager();
	}
	return p_ui;
}

void UIManager::destroyInstance()
{
	CC_SAFE_DELETE(p_ui);
	p_ui=nullptr;
}

