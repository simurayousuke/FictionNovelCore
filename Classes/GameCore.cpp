#include "GameCore.h"

USING_NS_CC;
using namespace CocosDenshion;

GameCore* GameCore::instance = NULL;
//int GameCore::currentId = 0;
//Stage GameCore::currentStage = Stage();
//std::map<int, Stage> GameCore::stageMap = std::map<int, Stage>();

GameCore::GameCore()
{

}

/*
GameCore::GameCore(const GameCore&)
{

}


GameCore& GameCore::operator=(const GameCore&)
{
	return *(GameCore::getInstance());
}
*/
GameCore* GameCore::getInstance()
{
	if (instance == NULL)
		instance = new GameCore();
	return instance;
}

void GameCore::init()
{
	//装载载入scene
	//auto scene = MainTitleScene::createScene();
	//Director::getInstance()->runWithScene(scene);

	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("local/" + Config::getInstance()->getLocalLanguage() + "/stages.xml");//读取xml文档,放入ValueVector中

	for (auto& e : txt_vec)
	{
		Stage stage;
		auto thisStageMap = e.asValueMap();//将键值转化成Map格式，放入txt_map中
		bool hasButton = (thisStageMap.at("hasbutton").asString() == "true");
		stage.setHasButton(hasButton);

		stage.setContext(thisStageMap.at("context").asString());
		stage.setFont(thisStageMap.at("font").asString());
		stage.setFontSize(thisStageMap.at("fontsize").asInt());
		if (hasButton)
		{
			int buttonNum = thisStageMap.at("buttonnum").asInt();
			Button* buttons = new Button[buttonNum];
			for (int i = 0; i < buttonNum; ++i)
			{
				buttons[i].setContext(thisStageMap.at("button" + std::to_string(i) + "context").asString());
				buttons[i].setFont(thisStageMap.at("button" + std::to_string(i) + "font").asString());
				buttons[i].setNextId(thisStageMap.at("button" + std::to_string(i) + "nextid").asInt());
				buttons[i].setFontSize(thisStageMap.at("button" + std::to_string(i) + "fontsize").asInt());
			}
			stage.setButtonNum(buttonNum);
			stage.setButtons(buttons);
		}
		else
			stage.setNextId(thisStageMap.at("nextid").asInt());

		auto bgm = thisStageMap.at("bgm").asString();
		stage.setBgm(bgm);
		if (bgm != "")
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic(("sounds/bgm/" + bgm).c_str());//wav,mp3,mid

		stage.setBg(thisStageMap.at("bg").asString());
		stage.setConversationBg(thisStageMap.at("conversationbg").asString());

		auto voice = thisStageMap.at("voice").asString();
		stage.setVoice(voice);
		if (voice != "")
			SimpleAudioEngine::getInstance()->preloadEffect(("sounds/voice/" + Config::getInstance()->getVoiceLanguage() + "/" + voice).c_str());//wav,mid

		stageMap[thisStageMap.at("id").asInt()] = stage;
	}
	run();

}

GameCore::~GameCore()
{
	delete instance;
}


void GameCore::nextStage()
{
	StatusManager::getInstance()->setCurrentId(StatusManager::getInstance()->getCurrentStage()->getNextId());
	loadStage();
}

void GameCore::nextStage(int id)
{
	StatusManager::getInstance()->setCurrentId(id);
	loadStage();
}

void GameCore::loadStage()
{
	if (StatusManager::getInstance()->getCurrentId() == -1)
	{
		//游戏结束

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif

	}
	else
	{
		StatusManager::getInstance()->setCurrentStage(&stageMap.at(StatusManager::getInstance()->getCurrentId()));
		//auto scene = GameScene::createScene(StatusManager::getInstance()->getCurrentStage());
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void GameCore::run()
{
	StatusManager::getInstance()->setCurrentId(0);
	StatusManager::getInstance()->setCurrentStage(&stageMap.at(StatusManager::getInstance()->getCurrentId()));
	//auto scene = GameScene::createScene(StatusManager::getInstance()->getCurrentStage());
	auto scene = GameScene::createScene();
	Director::getInstance()->runWithScene(scene);
}
/*
void GameCore::playBgm(std::string bgm)
{
	if (bgm != StatusManager::getInstance()->getCurrentBgm())
		SimpleAudioEngine::getInstance()->playBackgroundMusic(("sounds/bgm/" + bgm).c_str(), false);
}
void GameCore::playVoice(std::string voice)
{
	//SimpleAudioEngine::getInstance()->stopAllEffects();
	auto cv = StatusManager::getInstance()->getCurrentVoice();
	if (cv != 0)
		SimpleAudioEngine::getInstance()->stopEffect(cv);
	StatusManager::getInstance()->setCurrentVoice(SimpleAudioEngine::getInstance()->playEffect(("sounds/voice/" +voice).c_str(), false));
}
void GameCore::stopBgm()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
*/