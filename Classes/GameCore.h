#ifndef  _GAME_CORE_H_
#define  _GAME_CORE_H_

#include "cocos2d.h"
#include "Stage.h"
#include "GameScene.h"
#include "StatusManager.h"
#include <map>
#include "SimpleAudioEngine.h"

class GameCore
{
public:
	static GameCore* getInstance();
	void nextStage();
	void nextStage(int id);
	void init();
	void run();
	//void playBgm(std::string bgm);
	//void stopBgm();
	//void playVoice(std::string voice);
	~GameCore();
private:
	static GameCore* instance;
	void loadStage();
	GameCore();
	//把复制构造函数和=操作符也设为私有,防止被复制
	//GameCore(const GameCore&);
	//GameCore& operator=(const GameCore&);
	std::map<int, Stage> stageMap;
	/*
		0.context
		1.nextId
	*/
	//Stage currentStage;
	//int currentId;
};

#endif // _GAME_CORE_H_

