#include "StatusManager.h"
StatusManager* StatusManager::instance=NULL;

StatusManager* StatusManager::getInstance()
{
	if (instance == NULL)
		instance = new StatusManager();
	return instance;
}
StatusManager::StatusManager() {}
StatusManager::~StatusManager() {}
/*
void StatusManager::setGameScene(GameScene *gs)
{
	gameScene = gs;
}
GameScene* StatusManager::getGameScene()
{
	return gameScene;
}
*/

Stage* StatusManager::getCurrentStage()
{
	return currentStage;
}
int StatusManager::getCurrentId()
{
	return currentId;
}
void StatusManager::setCurrentStage(Stage* stg)
{
	currentStage = stg;
}
void StatusManager::setCurrentId(int id)
{
	currentId = id;
}