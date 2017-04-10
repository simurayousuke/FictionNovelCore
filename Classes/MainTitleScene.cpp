#include "MainTitleScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

std::string MainTitleScene::titleContext = "Game";
std::string MainTitleScene::titleBg = "game.png";
std::string MainTitleScene::titleFont = "";
int MainTitleScene::titleFontSize = 40;
std::string MainTitleScene::bgm = "stop";
int MainTitleScene::buttonNum = 0;
cocos2d::Rect* MainTitleScene::buttonRect = NULL;
std::string MainTitleScene::start = "Start";
std::string MainTitleScene::load = "Load";
std::string MainTitleScene::settings = "Settings";
std::string MainTitleScene::exit = "Exit";
std::string MainTitleScene::about = "About";

Scene* MainTitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainTitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainTitleScene::init()
{
	if (!Layer::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto tempFont = titleFont == "" ? Local::getDefaultFont() : titleFont;
	auto label = Label::createWithTTF(titleContext, "fonts/" + tempFont, titleFontSize);
	label->setDimensions(visibleSize.width / 3, Config::titleHeight);
	label->setPosition(Vec2(origin.x + label->getContentSize().width / 2 + 50, origin.y + visibleSize.height - label->getContentSize().height / 2 - 20));
	this->addChild(label, 2);

	auto bg = Sprite::create("assets/" + titleBg);
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setAnchorPoint(Point(0.5, 0.5));
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);


	if (bgm != "")
		if (bgm == "stop")
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			StatusManager::getInstance()->setCurrentBgm("stop");
		}
		else if (StatusManager::getInstance()->getCurrentBgm() != bgm)
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic(("sounds/bgm/" + bgm).c_str(), false);
			StatusManager::getInstance()->setCurrentBgm(bgm);
		}
	/*
	0.Start
	1.Load
	2.Settings
	3.Exit
	4.About
	*/

	buttonNum = 5;
	buttonRect = new Rect[buttonNum];
	std::string context[5] = { start,load,settings,exit,about };
	
	for (int i = 0; i < buttonNum; ++i)
	{
		auto buttonItem0 = Label::createWithTTF(context[i], "fonts/" + Local::getDefaultFont(), 30);
		buttonItem0->setPosition(Vec2(origin.x + visibleSize.width - 50 - buttonItem0->getContentSize().width / 2,
			origin.y + visibleSize.height - Config::titleHeight - visibleSize.height*0.2) / buttonNum*(5 - i));
		this->addChild(buttonItem0, 2);
		auto buttonBg = Sprite::create("assets/conversationBg.png");
		buttonBg->setPosition(Vec2(origin.x + visibleSize.width - 50 - buttonItem0->getContentSize().width / 2,
			origin.y + visibleSize.height - Config::titleHeight - visibleSize.height*0.2) / buttonNum*(5 - i));
		buttonBg->setScale((buttonItem0->getContentSize().width + 50) / buttonBg->getContentSize().width, (buttonItem0->getContentSize().height + 20) / buttonBg->getContentSize().height);
		this->addChild(buttonBg, 1);
		buttonRect[i] = buttonBg->getBoundingBox();
	}

	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{

	};
	myKeyListener->onKeyReleased = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{

	};

	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseMove = [=](Event *event)
	{
		//EventMouse* e = (EventMouse*)event;
		//this->mouse->setPosition(e->getCursorX(), e->getCursorY() + visibleSize.height);
	};
	myMouseListener->onMouseUp = [=](Event *event)
	{

	};
	myMouseListener->onMouseDown = [=](Event *event)
	{
		EventMouse* e = (EventMouse*)event;
		Vec2 position = e->getLocationInView();
		int buttonId = -1;
		if (e->getMouseButton() == 0)//L0,R1
		{
			for (int i = 0; i < buttonNum; ++i)
				if (buttonRect[i].containsPoint(position))
				{
					buttonId = i;
					break;
				}
			switch (buttonId)
			{
			case 0:
				SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				StatusManager::getInstance()->setCurrentBgm("stop");
				GameCore::getInstance()->run();
				break;
			case 1:
				StatusManager::getInstance()->load();
				break;
			case 2:
				GameCore::getInstance()->settings();
				break;
			case 3:
				GameCore::getInstance()->end();
				break;
			case 4:
				break;
			default:
				break;
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
	return true;
}