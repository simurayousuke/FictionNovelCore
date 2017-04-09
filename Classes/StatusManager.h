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
	void setCurrentStage(Stage* stg);
	void setCurrentId(int id);
	//void save();
	//void load();
private:
	StatusManager();
	//GameScene* gameScene;
	static StatusManager* instance;
	Stage* currentStage=NULL;
	int currentId=0;
};

#endif // _STATUS_MANAGER_H_

