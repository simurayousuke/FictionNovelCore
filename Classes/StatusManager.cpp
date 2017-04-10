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

Stage* StatusManager::getCurrentStage()
{
	return currentStage;
}
int StatusManager::getCurrentId()
{
	return currentId;
}
std::string StatusManager::getCurrentBgm()
{
	return currentBgm;
}
unsigned int StatusManager::getCurrentVoice()
{
	return currentVoice;
}

void StatusManager::setCurrentStage(Stage* stg)
{
	currentStage = stg;
}
void StatusManager::setCurrentId(int id)
{
	currentId = id;
}
void StatusManager::setCurrentBgm(std::string bgm)
{
	currentBgm = bgm;
}
void StatusManager::setCurrentVoice(unsigned int voice)
{
	currentVoice = voice;
}