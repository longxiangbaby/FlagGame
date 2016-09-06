#ifndef  __PLAYER_H__
#define  __PLAYER_H__
#include "Camp.h"

class Player :public Camp
{
public:
	Player(void);
	~Player(void);

	static Player* createPlayer();

	bool init();


};
#endif
