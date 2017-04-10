#ifndef  _STATUS_MANAGER_H_
#define  _STATUS_MANAGER_H_

#include "cocos2d.h"
#include "GameScene.h"

class StatusManager
{
public:
	static StatusManager* getInstance();
	//void setGameScene(GameScene *gs);
	//GameScene* getGameScene();
	~StatusManager();
	Stage* getCurrentStage();
	int getCurrentId();
	std::string getCurrentBgm();//////////////
	unsigned int getCurrentVoice();
	void setCurrentStage(Stage* stg);
	void setCurrentId(int id);
	void setCurrentBgm(std::string bgm);//////////////
	void setCurrentVoice(unsigned int voice);
	//void save();
	//void load();
private:
	StatusManager();
	//GameScene* gameScene;
	static StatusManager* instance;
	Stage* currentStage=NULL;
	int currentId=0;
	std::string currentBgm="stop";
	unsigned int currentVoice=0;
};

#endif // _STATUS_MANAGER_H_

