#include "RoomLayer.h"
#include "manager\UIManager.h"


RoomLayer::RoomLayer(void)
{
	rootPath="ui/XiaowuUI.ExportJson";
	panelName="XWu_Panel";
}


RoomLayer::~RoomLayer(void)
{
}

bool RoomLayer::init()
{
	if (!BaseLayer::init())
		return false;
	ImageView* xwu_veiw=static_cast<ImageView*>(rootPanel->getChildByName("xwu_view"));
	return true;
}


void RoomLayer::onTouchEvent(Ref* pSender, TouchEventType type)
{

}
