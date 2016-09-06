#include "MapLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include <hash_map>
#include "UITextField.h"
#include <math.h>
#include "UIText.h"
#include "manager/UIManager.h"
#include "CityLayer.h"
#include "city/City.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio; 
using namespace std;  
enum 
{
	kTagTileMap = 1,
};

const double Pi=3.14159265358979;

MapLayer::MapLayer(void)
{

}

MapLayer::~MapLayer(void)
{

}

bool MapLayer::loadMap(const std::string &str)
{
	p_map = TMXTiledMap::create(str);
	this->addChild(p_map,0,1);

	auto map = static_cast<TMXTiledMap*>( getChildByTag(kTagTileMap) );

	auto group = map->getObjectGroup("object");
	auto& objects = group->getObjects();
	hash_map<const string, City*> hmap;

	auto s = map->getContentSize();
	CCLOG("ContentSize: %f, %f", s.width,s.height);
	//map->setPosition(Point(-s.width/2,0));

	TMXLayer* tmxlayer=map->getLayer("ground");
	Size tileSize=map->getTileSize();
	
	CCLOG("point: x: %d y: %d",map->getChildrenCount(),map->getPositionY());

	for (auto& obj : objects)
	{
		ValueMap& dict = obj.asValueMap();

		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float col = dict["xpos"].asFloat();
		float row = dict["ypos"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		string name=dict["name"].asString();
		//auto 
		City* city=City::create();
		
		city->setLabel(name);

		double r=45*Pi/180;
		float x1= x*cos(r)+y*sin(r);
		float y1= y*cos(r)-x*sin(r);

		tmxlayer->getTileAt(Point(col,row));
		Point local=tmxlayer->getPositionAt(Point(int(col) ,int(row)));

		//CCLOG("%s point: x: %f y: %f",name.c_str(),x1,y1);


		//TTFConfig config2("fonts/arial.ttf",30);//��ʼ��TTFConfig����һ������Ϊ�ֿ��·�����ڶ�������Ϊ�����С  
		//auto label = Label::createWithTTF(config2,name,TextHAlignment::LEFT);//����label�����������  
		//label->setPosition(Point(local.x+width,local.y+height));
		//label->setAnchorPoint(Point::ANCHOR_MIDDLE);//����ê�����  
		//label->enableOutline(Color4B::BLACK, 5);		//���ñ߿����ɫΪ��ɫ  

		//auto label = Label::create(name, "arial", 18);
		//label->setColor(Color3B::WHITE);  
		//label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		////�����ڲ���ɫΪ��ɫ  
		//label->setPosition(local.x+width,local.y+height);
		//label->enableShadow();
		//Text* text=Text::create(name, "arial", 18);
		//text->setPosition(Point(local.x+width,local.y+height));


		city->setAnchorPoint( Point(0.5f, 0.5f) );

		city->setPosition(Point(local.x+width,local.y+height));
		CCLOG("XX point: x: %f y: %f",city->getPositionX(),city->getPositionY());

		hmap[name]=city;
		//Point point=map->convertToNodeSpace(city->getPosition());

		//CCLOG("XX point: x: %f y: %f",x,y);

		p_map->addChild(city,2);		
	}
	 //kmGLPopMatrix();
	return true;
}

//����Ļ�����㻻��� Map������(45���ӽǵ�ͼ)
//bool CIsoMapLayer::GetTilePosFromScreenPos( const CCPoint ptTouchPoint,CCPoint &ptTilePos )
//{
//	do 
//	{
//		CCTMXTiledMap* pIOSMap = dynamic_cast<CCTMXTiledMap*>(getChildByTag(enTagMap));
//		CC_BREAK_IF(pIOSMap==NULL);
//		//����У��
//		CC_BREAK_IF(pIOSMap->getMapSize().width==0||pIOSMap->getMapSize().height==0);
//
//
//		//����Ļ���� ת���� Map�ڵ� ������
//		CCPoint ptMapPoint = pIOSMap->convertToNodeSpace(ptTouchPoint);
//
//		CCSize sizeMap = pIOSMap->getMapSize();
//		CCSize sizeTile = pIOSMap->getTileSize();
//		CCSize sizeNode = pIOSMap->getContentSize();
//
//		float fTileSin = GetSinFromMap(pIOSMap);//����Sin�ǣ����û����б�д
//		float fTileCos = GetCosFromMap(pIOSMap);//����Cos�ǣ����û����б�д
//		float fTileTan = sizeTile.height/sizeTile.width;
//
//		CC_BREAK_IF(fTileSin==0||fTileCos==0);
//
//		//��ͼ����������ϵ�´�С
//		float fTileWidth = sizeTile.width*0.5f/fTileCos;
//		float fTileHeight = sizeTile.height*0.5f/fTileSin;//ֵӦ����Weight��ͬ����Ϊ�����ϻ��Ƿ����
//
//		//��ͼ�ܴ�С(������ϵ��)
//		float fMapTotalWidth =fTileWidth*sizeMap.width;
//		float fMapTotalHeight =fTileHeight*sizeMap.height;//��ͼ����Size��һ���Ƿ��ε�
//
//		//����ϵ�任��ʽ
//		float fMapPosX = (ptMapPoint.x-(ptMapPoint.y-sizeNode.height*0.5f)/fTileTan)*0.5f/fTileCos;
//
//		int nXPos = (int)(fMapPosX/fTileWidth);
//
//		float fMapPosY = (ptMapPoint.y-sizeNode.height*0.5f)*0.5f/fTileSin+ptMapPoint.x*0.5f/fTileCos;
//		int nYPos =(int)(fMapPosY/fTileHeight);
//
//		//����Ƿ����ڵ�ͼ��
//		if(nYPos<0||nXPos<0)return false;
//		if(nYPos>=sizeMap.height||nXPos>=sizeMap.width)return false;
//
//		//�õ���ͼ������
//		ptTilePos = ccp(nXPos,pIOSMap->getMapSize().height-1-nYPos);
//
//		return true;
//	} while (false);
//	return false;
//}

MapLayer* MapLayer::createMap()
{
	MapLayer* maplayer=new MapLayer();
	if (maplayer && maplayer->init())
	{
		maplayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(maplayer);
	}
	return maplayer;
}

void MapLayer::onEnter()
{
	Layer::onEnter();

	Director::getInstance()->setProjection(Director::Projection::_2D);
	Director::getInstance()->setDepthTest(true);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(MapLayer::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->setPosition(-1000,-500);

}

void MapLayer::onExit()
{
	Layer::onExit();
	Director::getInstance()->setProjection(Director::Projection::DEFAULT);
	Director::getInstance()->setDepthTest(false);
	
}

void MapLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	auto touch = touches[0];
	auto diff = touch->getDelta();
	auto node = getChildByTag(kTagTileMap);
	auto currentPos = node->getPosition();

	node->setPosition(currentPos + diff);
}

void MapLayer::onTouchEvent(Ref* pSender, TouchEventType type)
{
	CCLOG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX!");
	if (type==TOUCH_EVENT_BEGAN)
	{
		UIManager::getInstance()->open(CityLayer::create());
	}
}
