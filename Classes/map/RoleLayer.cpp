#include "RoleLayer.h"
#include "ui/UIWidget.h"
#include "CocosGUI.h"
#include "manager/UIManager.h"


RoleLayer::RoleLayer(void)
{
	rootPath="ui/RoleUI.ExportJson";
	panelName="Role_Panel";
}


RoleLayer::~RoleLayer(void)
{

}

bool RoleLayer::init()
{
	if (!BaseLayer::init())
		return false;
	ImageView* role_veiw=static_cast<ImageView*>(rootPanel->getChildByName("role_view"));
	return true;
}

void RoleLayer::onTouchEvent(Ref* pSender, TouchEventType type)
{

}
