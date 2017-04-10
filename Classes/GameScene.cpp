#include "GameScene.h"


USING_NS_CC;
using namespace CocosDenshion;

int GameScene::buttonNum = 0;
Stage* GameScene::stage = NULL;
int* GameScene::nextId = NULL;
cocos2d::Rect* GameScene::buttonRect = NULL;
cocos2d::Rect GameScene::textRect = cocos2d::Rect();

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
	0.背景图
	1.框图
	2.文字
*/
bool GameScene::init()
{
	if (!Layer::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (stage == NULL)
		stage = StatusManager::getInstance()->getCurrentStage();

	//debug
	/*
	std::string d = "";
	std::vector<std::string>* vec = Config::getInstance()->getSupportLanguage();
	for (auto s: *vec)
	{
		d += s;
		d += "\n";
	}
	auto debug = Label::createWithSystemFont(d, "TimesNewRoman", 24);
	debug->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(debug, 3);
	*/
	//end

	auto label = Label::createWithTTF(stage->getContext(), "fonts/" + stage->getFont(), stage->getFontSize());
	label->setDimensions(visibleSize.width - 50, Config::conversationHeight);
	label->setPosition(Vec2(origin.x + label->getContentSize().width / 2 + 50, origin.y + label->getContentSize().height / 2));
	this->addChild(label, 2);

	auto bg = Sprite::create("assets/" + stage->getBg());
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setAnchorPoint(Point(0.5, 0.5));
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);

	if (stage->getBgm() != "")
		if (stage->getBgm() == "stop")
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			StatusManager::getInstance()->setCurrentBgm("stop");
		}
		else if( StatusManager::getInstance()->getCurrentBgm()!= stage->getBgm())
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic(("sounds/bgm/" + stage->getBgm()).c_str(), false);
			StatusManager::getInstance()->setCurrentBgm(stage->getBgm());
		}

	if (stage->getVoice() != "")
	{
		auto cv = StatusManager::getInstance()->getCurrentVoice();
		if (cv != 0)
			SimpleAudioEngine::getInstance()->stopEffect(cv);
		StatusManager::getInstance()->setCurrentVoice(SimpleAudioEngine::getInstance()->playEffect(("sounds/voice/" + stage->getVoice()).c_str(), false));
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
	textRect = conversationBg->getBoundingBox();

	if (stage->hasButton())
	{
		buttonNum = stage->getButtonNum();
		Button* buttons = stage->getButtons();
		buttonRect = new Rect[buttonNum];
		nextId = new int[buttonNum];
		for (int i = 0; i < buttonNum; ++i)
		{
			//建立button
			auto buttonItem = Label::createWithTTF(buttons[i].getContext(), "fonts/" + buttons[i].getFont(), buttons[i].getFontSize());
			//buttonItem->setDimensions(visibleSize.width - 50, Config::conversationHeight);
			buttonItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (visibleSize.height - Config::conversationHeight - visibleSize.height*0.2) / buttonNum*(i + 1)));
			this->addChild(buttonItem, 2);

			auto buttonBg = Sprite::create("assets/conversationBg.png");
			buttonBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (visibleSize.height - Config::conversationHeight - visibleSize.height*0.2) / buttonNum*(i + 1)));
			buttonBg->setScale((buttonItem->getContentSize().width + 50) / buttonBg->getContentSize().width, (buttonItem->getContentSize().height + 20) / buttonBg->getContentSize().height);
			this->addChild(buttonBg, 1);

			nextId[i] = buttons[i].getNextId();
			buttonRect[i] = buttonBg->getBoundingBox();
		}
	}
	auto myKeyListener = EventListenerKeyboard::create(); //创建事件监听器监听键盘事件
														  //键盘按键按下时的响应
	myKeyListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		CCLOG("key is pressed, keycode is %d", keycode);
	};

	//键盘按键弹回时的响应
	myKeyListener->onKeyReleased = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		CCLOG("key is released, keycode is %d", keycode);
	};

	auto myMouseListener = EventListenerMouse::create();//创建事件监听器鼠标事件
														//鼠标移动
	myMouseListener->onMouseMove = [=](Event *event)
	{
		//EventMouse* e = (EventMouse*)event;
		//this->mouse->setPosition(e->getCursorX(), e->getCursorY() + visibleSize.height);
	};

	myMouseListener->onMouseDown = [=](Event *event)
	{
		//this->mouse->setScale(0.2f); //鼠标按键按下，屏幕上的“箭头”尺寸缩小
		EventMouse* e = (EventMouse*)event;
		Vec2 position = e->getLocationInView();

		if (e->getMouseButton() == 0)//L0,R1
		{
			if (StatusManager::getInstance()->getCurrentStage()->hasButton())
				for (int i = 0; i < buttonNum; ++i)
					if (buttonRect[i].containsPoint(position))
						GameCore::getInstance()->nextStage(nextId[i]);
			if (textRect.containsPoint(position)&&!StatusManager::getInstance()->getCurrentStage()->hasButton())
				GameCore::getInstance()->nextStage();
		}
	};

	myMouseListener->onMouseUp = [=](Event *event)
	{
		//this->mouse->setScale(0.3f); //鼠标按键抬起，屏幕上的“箭头”尺寸放大
	};

	//将事件监听器与场景绑定
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

	stage = NULL;
	return true;
}

