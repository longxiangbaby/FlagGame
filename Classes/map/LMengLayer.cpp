#include "LMengLayer.h"
#include "manager\UIManager.h"


LMengLayer::LMengLayer(void)
{
	rootPath="ui/LianMenUI.ExportJson";
	panelName="LMen_Panel";
}


LMengLayer::~LMengLayer(void)
{

}

bool LMengLayer::init()
{
	if (!BaseLayer::init())
		return false;
	ImageView* lmen_view=static_cast<ImageView*>(rootPanel->getChildByName("lmen_view"));
	return true;
}

void LMengLayer::onTouchEvent(Ref* pSender, TouchEventType type)
{

}
