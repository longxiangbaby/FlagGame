#ifndef  __GAME_CONTROL_H__
#define  __GAME_CONTROL_H__
#include "game\Player.h"
#include "cocos2d.h"
#include "game\Camp.h"
#include "manager\UIManager.h"

USING_NS_CC;

class GameControl:public cocos2d::Ref
{
public:
	GameControl(void);
	~GameControl(void);

	static GameControl* getInstance();

	static void destroy();

	bool init();

	Player* getPlayer();

	Camp* getCamp(int flag);

	void addCamp(Camp* camp);

	void addCity(City* city);

	City* getCity(int id);

	void update(float delta);

	void pause();

	void start();
protected:
	Player* player;
	Map<int,Camp*> m_camps;
	Map<int,City*> m_citys;
	CC_SYNTHESIZE(City*,city,City);
	bool isPause;
};
#endif
