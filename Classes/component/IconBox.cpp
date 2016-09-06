#include "IconBox.h"


IconBox::IconBox(void):index(0)
{
}


IconBox::~IconBox(void)
{
}

IconBox* IconBox::createIconBox(string path)
{
	IconBox* iconBox=new IconBox();
	if (iconBox&&iconBox->initBox(path))
	{
		iconBox->autorelease();
	}else{
		CC_SAFE_DELETE(iconBox);
	}
	return iconBox;
}

void IconBox::setIndex(int index)
{
	this->index=index;
	getAnimation()->playWithIndex(0);
	getAnimation()->gotoAndPause(index);
}

int IconBox::getIndex()
{
	return index;
}

bool IconBox::initBox(string path)
{
	if (!Armature::init(path))
	{
		return false;
	}
	setIndex(index);
	//setAnchorPoint(ccp(0.5,0.5));

	//GUIReader
	return true;
}


