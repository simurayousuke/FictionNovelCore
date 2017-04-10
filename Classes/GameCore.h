#ifndef  _GAME_CORE_H_
#define  _GAME_CORE_H_

#include "cocos2d.h"
#include "Stage.h"
#include "GameScene.h"
#include "StatusManager.h"
#include <map>
#include "SimpleAudioEngine.h"
#include "MainTitleScene.h"

class GameCore
{
public:
	static GameCore* getInstance();
	void nextStage();
	void nextStage(int id);
	void init();
	void run();
	void end();
	void reload();
	~GameCore();
private:
	static GameCore* instance;
	void loadStage();
	void preloadMainTitle();
	void preloadStages();
	void preloadConfig();
	GameCore();
	std::map<int, Stage> stageMap;
};

#endif // _GAME_CORE_H_

