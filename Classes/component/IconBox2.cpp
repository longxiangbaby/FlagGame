#include "IconBox2.h"
#include "util\StringUtil.h"


IconBox2::IconBox2(void)
{
}


IconBox2::~IconBox2(void)
{
}

IconBox2* IconBox2::createBox(string path)
{
	IconBox2* iconBox=new IconBox2();
	if (iconBox&& iconBox->initBox(path))
	{
		iconBox->autorelease();
	}
	return iconBox;
}

bool IconBox2::initBox(string path)
{
	if (Sprite::init())
	{
		this->path=path;
	}
	return true;
}

void IconBox2::setIndex(int index)
{
	this->stopAllActions(); 
	this->setTexture(StringUtil::StringAddInt(path,index)+".png");
	this->index=index;
	//SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName("00001.png"); 
	//this->setDisplayFrame(frame);
}

int IconBox2::getIndex()
{
	return index;
}
