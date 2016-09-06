#include "CityLayer.h"


CityLayer::CityLayer(void)
{
	rootPath="ui/CityUI.ExportJson";
	panelName="City_Panel";
}


CityLayer::~CityLayer(void)
{

}

bool CityLayer::init()
{
	if (!BaseLayer::init())
		return false;
	ImageView* city_view=static_cast<ImageView*>(rootPanel->getChildByName("city_view"));
	
	return true;
}
