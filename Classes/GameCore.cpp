#include "GameCore.h"

USING_NS_CC;

GameCore* GameCore::instance = NULL;
int GameCore::currentId = 0;
Stage GameCore::currentStage = Stage();
std::map<int, Stage> GameCore::stageMap = std::map<int, Stage>();

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

	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("local/cn/stages.xml");//读取xml文档,放入ValueVector中
																							
	for (auto& e : txt_vec)
	{
		Stage stage;
		auto thisStageMap = e.asValueMap();//将键值转化成Map格式，放入txt_map中
		bool hasButton = thisStageMap.at("hasbutton").asString() == "true" ? true : false;

		stage.setContext(thisStageMap.at("context").asString());
		stage.setFont(thisStageMap.at("font").asString());
		if (hasButton)
		{
			int buttonNum = thisStageMap.at("buttonnum").asInt();
			Button* buttons = new Button[buttonNum];
			for (int i = 0; i < buttonNum; ++i)
			{
				buttons[i].setContext(thisStageMap.at("button" + std::to_string(i) + "context").asString());
				buttons[i].setFont(thisStageMap.at("button" + std::to_string(i) + "font").asString());
				buttons[i].setNextId(thisStageMap.at("button" + std::to_string(i) + "nextid").asInt());
			}
			stage.setButtonNum(buttonNum);
			stage.setButtons(buttons);
		}
		else
			stage.setNextId(thisStageMap.at("nextid").asInt());
		stage.setBgm(thisStageMap.at("bgm").asString());
		stage.setBg(thisStageMap.at("bg").asString());
		stage.setConversationBg(thisStageMap.at("conversationbg").asString());
		stage.setVoice(thisStageMap.at("voice").asString());
		stageMap[thisStageMap.at("id").asInt()] = stage;
	}
	run();

}

GameCore::~GameCore()
{
	delete instance;
}

Stage GameCore::getCurrentStage()
{
	return currentStage;
}

void GameCore::nextStage()
{
	currentId = currentStage.getNextId();
	if (currentId == -1)
	{
		//exit
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif

	}
	else
	{
		currentStage = stageMap.at(currentId);
		auto scene = GameScene::createScene(currentStage.getContext());
		Director::getInstance()->replaceScene(scene);
	}
}

void GameCore::run()
{
	currentId = 0;
	currentStage = stageMap.at(currentId);
	auto scene = GameScene::createScene(currentStage.getContext());
	Director::getInstance()->runWithScene(scene);
}