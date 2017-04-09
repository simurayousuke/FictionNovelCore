#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

std::string GameScene::titleStr = "";
Stage* GameScene::stage = NULL;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

cocos2d::Scene* GameScene::createScene(Stage* stg)
{
	stage = stg;
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
/*
	0.±³¾°Í¼
	1.¿òÍ¼
	2.ÎÄ×Ö
*/
bool GameScene::init()
{
	if (!Layer::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create("assets/CloseNormal.png", "assets/CloseSelected.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	if (stage == NULL)
		stage = StatusManager::getInstance()->getCurrentStage();

	auto label = Label::createWithTTF(stage->getContext(), "fonts/" + stage->getFont(), stage->getFontSize());
	label->setPosition(Vec2(origin.x + label->getContentSize().width / 2 + 50, origin.y + Config::conversationHeight));
	//label->setDimensions(visibleSize.width-50, Config::conversationHeight);
	this->addChild(label, 2);

	auto bg = Sprite::create("assets/" + stage->getBg());
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setAnchorPoint(Point(0.5, 0.5));
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);

	if (stage->getBgm() != "")
	{

	}

	if (stage->getVoice() != "")
	{

	}

	auto conversationBgPath = stage->getConversationBg();
	if (conversationBgPath == "")
		conversationBgPath = "conversationBg.png";
	auto conversationBg = Sprite::create("assets/" + conversationBgPath);
	conversationBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + Config::conversationHeight * 5 / 8));
	conversationBg->setAnchorPoint(Point(0.5, 0.5));
	conversationBg->setScale((visibleSize.width - 20) / conversationBg->getContentSize().width, Config::conversationHeight / conversationBg->getContentSize().height);
	conversationBg->setOpacity(200);
	this->addChild(conversationBg, 1);

	if (stage->hasButton())
	{
		int buttonNum = stage->getButtonNum();
		Button* buttons = stage->getButtons();
		for (int i = 0; i < buttonNum; ++i)
		{
			//½¨Á¢button
			auto buttonItem = MenuItemFont::create(buttons[i].getContext(), CC_CALLBACK_1(GameScene::buttonClickCallback, this, buttons[i].getNextId()));
			buttonItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (visibleSize.height - Config::conversationHeight - visibleSize.height*0.2) / buttonNum*(i + 1)));
			auto buttonMenu = Menu::create(buttonItem, NULL);
			buttonMenu->setPosition(Vec2::ZERO);
			this->addChild(buttonMenu, 1);
		}
	}

	stage = NULL;
	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
	GameCore::getInstance()->nextStage();
}

void GameScene::buttonClickCallback(Ref* pSender, int id)
{
	GameCore::getInstance()->nextStage(id);
}

