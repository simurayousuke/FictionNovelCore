#include "GameCore.h"

USING_NS_CC;
using namespace CocosDenshion;

GameCore* GameCore::instance = NULL;

GameCore::GameCore()
{

}

GameCore* GameCore::getInstance()
{
	if (instance == NULL)
		instance = new GameCore();
	return instance;
}

void GameCore::init()
{
	preloadConfig();
	reload();
	firstLoad = false;

	auto title = MainTitleScene::createScene();
	Director::getInstance()->replaceScene(title);
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
		auto scene = MainTitleScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		StatusManager::getInstance()->setCurrentStage(&stageMap.at(StatusManager::getInstance()->getCurrentId()));
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void GameCore::run()
{
	StatusManager::getInstance()->setCurrentId(0);
	StatusManager::getInstance()->setCurrentStage(&stageMap.at(StatusManager::getInstance()->getCurrentId()));
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameCore::end()
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameCore::preloadConfig()
{
	ValueVector configVec = FileUtils::getInstance()->getValueVectorFromFile("config.xml");
	auto configMap = configVec.at(0).asValueMap();
	Config::getInstance()->setGameName(configMap.at("gamename").asString());
	auto supportLanguage = configMap.at("supportlanguage").asString();
	std::string lang;
	std::string::size_type pos;
	std::vector<std::string>* supportLanguages = new std::vector<std::string>();
	supportLanguage += ",";//扩展字符串以方便操作
	size_t size = supportLanguage.size();
	for (size_t i = 0; i < size; i++)
	{
		pos = supportLanguage.find(",", i);
		if (pos < size)
		{
			std::string s = supportLanguage.substr(i, pos - i);
			supportLanguages->push_back(s);
			i = pos;
		}
	}
	Config::getInstance()->setSupportLanguage(supportLanguages);
	lang = Config::getInstance()->getDefaultTextLanguage();
	if (lang == "none")
		Config::getInstance()->setLocalLanguage(configMap.at("defaultlanguage").asString());
	else
		Config::getInstance()->setLocalLanguage(lang);
	lang = Config::getInstance()->getDefaultVoiceLanguage();
	if (lang == "none")
		Config::getInstance()->setVoiceLanguage(configMap.at("defaultvoicelanguage").asString());
	else
		Config::getInstance()->setVoiceLanguage(lang);
}

void GameCore::preloadMainTitle()
{
	if (firstLoad)
		LoadScene::updateLabel(Local::loadingMainTitle);
	ValueVector titleVec = FileUtils::getInstance()->getValueVectorFromFile("local/" + Config::getInstance()->getLocalLanguage() + "/title.xml");
	auto titleMap = titleVec.at(0).asValueMap();
	MainTitleScene::titleContext = titleMap.at("titlecontext").asString();
	MainTitleScene::titleBg = titleMap.at("titlebg").asString();
	MainTitleScene::bgm = titleMap.at("titlebgm").asString();
	MainTitleScene::titleFont = titleMap.at("titlefont").asString();
	MainTitleScene::titleFontSize = titleMap.at("titlefontsize").asInt();
	MainTitleScene::start = titleMap.at("start").asString();
	MainTitleScene::load = titleMap.at("load").asString();
	MainTitleScene::settings = titleMap.at("settings").asString();
	MainTitleScene::exit = titleMap.at("exit").asString();
	MainTitleScene::about = titleMap.at("about").asString();
}

void GameCore::preloadStages()
{
	if (firstLoad)
		LoadScene::updateLabel(Local::loadingStages);
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
		{
			if (firstLoad)
				LoadScene::updateLabel(Local::loadingSound);
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic(("sounds/bgm/" + bgm).c_str());//wav,mp3,mid
		}

		stage.setBg(thisStageMap.at("bg").asString());
		stage.setConversationBg(thisStageMap.at("conversationbg").asString());

		auto voice = thisStageMap.at("voice").asString();
		stage.setVoice(voice);
		if (voice != "")
		{
			if (firstLoad)
				LoadScene::updateLabel(Local::loadingSound);
			SimpleAudioEngine::getInstance()->preloadEffect(("sounds/voice/" + Config::getInstance()->getVoiceLanguage() + "/" + voice).c_str());//wav,mid
		}
		stageMap[thisStageMap.at("id").asInt()] = stage;
	}
}

void GameCore::reload()
{
	preloadLocal();
	//装载载入scene

	if (firstLoad)
	{
		auto scene = LoadScene::createScene();
		Director::getInstance()->runWithScene(scene);
	}
	else
	{
		auto scene = LoadScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	preloadMainTitle();
	preloadStages();
	preloadSettingsScene();
	preloadLoadScene();
	preloadAboutScene();
}

void GameCore::preloadSettingsScene()
{
	if (firstLoad)
		LoadScene::updateLabel(Local::loadingSettingsScene);
	ValueVector configVec = FileUtils::getInstance()->getValueVectorFromFile("local/default.xml");
	auto configMap = configVec.at(0).asValueMap();

	SettingsScene::jp = configMap.at("jp").asString();
	SettingsScene::cn = configMap.at("cn").asString();
	SettingsScene::en = configMap.at("en").asString();
}

void GameCore::preloadLoadScene()
{

}

void GameCore::preloadAboutScene()
{

}

void GameCore::settings()
{
	auto scene = SettingsScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameCore::preloadLocal()
{
	ValueVector configVec = FileUtils::getInstance()->getValueVectorFromFile("local/" + Config::getInstance()->getLocalLanguage() + "/default.xml");
	auto configMap = configVec.at(0).asValueMap();

	Local::save = configMap.at("save").asString();
	Local::load = configMap.at("load").asString();
	Local::back = configMap.at("back").asString();

	Local::loading = configMap.at("loading").asString();
	Local::loadingConfig = configMap.at("loadingconfig").asString();
	Local::loadingLocal = configMap.at("loadinglocal").asString();
	Local::loadingSound = configMap.at("loadingsound").asString();
	Local::loadingMainTitle = configMap.at("loadingmaintitle").asString();
	Local::loadingSettingsScene = configMap.at("loadingsettingsscene").asString();
	Local::loadingStages = configMap.at("loadingstages").asString();
}