#ifndef  __GTWEEN_H__
#define  __GTWEEN_H__
#include "cocos2d.h"
#include <iostream>
#include "fight\TileGroup.h"
#include "util\ArrayUtil.h"

USING_NS_CC;
using namespace std;

struct GObject
{
	Node* souce;
	int x;
	int y;
	int vx;
	int vy;
	std::function<void()> complele;
};

struct GBlock
{
	Node* souce;
	int x;
	int y;
	int vx;
	int vy;
	std::function<void()> complele;
};

class GTween:public cocos2d::Ref
{
public:
	GTween();
	~GTween();

	static void to(Node* souce,int x,int y,int vx,std::function<void()> complele);;

	static void to(GObject obj);;

	static void run(Node* souce,int x,int y,int vx,std::function<void()> complele);;

	static void run(Node* souce,Animal* target,int v=5);

	static void update();
};

#endif
