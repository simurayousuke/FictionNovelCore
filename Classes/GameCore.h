#ifndef  _GAME_CORE_H_
#define  _GAME_CORE_H_

#include "cocos2d.h"
#include "Stage.h"
#include "GameScene.h"
#include <map>

class GameCore
{
public:
	static GameCore* getInstance();
	static Stage getCurrentStage();
	static void nextStage();
	static void init();
	static void run();
	~GameCore();
private:
	static GameCore* instance;
	GameCore();
	//把复制构造函数和=操作符也设为私有,防止被复制
	//GameCore(const GameCore&);
	//GameCore& operator=(const GameCore&);
	static std::map<int, Stage> stageMap;
	/*
		0.context
		1.nextId
	*/
	static Stage currentStage;
	static int currentId;
};

#endif // _GAME_CORE_H_

