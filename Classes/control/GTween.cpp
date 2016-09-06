#include "GTween.h"
#include "util\ArrayList.h"
#include "FightControl.h"

static ArrayList<GObject> nodes;
static ArrayList<GBlock> blocks;

GTween::GTween()
{

}

GTween::~GTween()
{

}

void GTween::update()
{
	int i=nodes.size() - 1;
	while(i>=0){
		GObject node=nodes.at(i);
		if ((node.vx>0&&node.souce->getPositionX()>=node.x)||
			(node.vx<0&&node.souce->getPositionX()<=node.x)) 
		{
			node.souce->setPositionX(node.x);
			node.complele();
			nodes.erase(i);

		}else{
			node.souce->setPositionX(node.souce->getPositionX()+node.vx);
		}
		i--;
	}

	int k=blocks.size()-1;

	while(k>=0){
		GBlock block=blocks.at(k);
		block.souce->setPositionX(block.souce->getPositionX()+block.vx);
		block.souce->setPositionY(block.souce->getPositionY()+block.vy);
		if (block.souce->getPositionY()>block.y)
		{
			FightControl::getInstance()->getGrid()->removeBlock(block.souce);
			blocks.erase(k);
		}
		k--;
	}
}

void GTween::to(GObject obj)
{
	nodes.pushBack(obj);
}

void GTween::to(Node* souce,int x,int y,int vx,std::function<void()> complele)
{
	GObject obj;
	obj.souce=souce;
	obj.complele=complele;
	obj.x=x;
	obj.y=y;
	obj.vx=vx;
	to(obj);
}

void GTween::run(Node* souce,int x,int y,int vx,std::function<void()> complele)
{

}


void GTween::run(Node* souce,Animal* target,int v/*=5*/)
{
	GBlock block;
	block.vx=(CCRANDOM_0_1()*10>5)?-2:2;
	block.vy=10;
	block.x=target->getAnimalSprite()->getPositionX()+10;
	block.y=target->getAnimalSprite()->getPositionY()+150;
	block.souce=souce;
	blocks.pushBack(block);
	FightControl::getInstance()->getGrid()->addEffctBlock(souce,target);
}

