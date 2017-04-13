#include "SettingsScene.h"


USING_NS_CC;
using namespace CocosDenshion;

int SettingsScene::buttonNum = 0;
cocos2d::Rect* SettingsScene::buttonRect = NULL;
cocos2d::Rect SettingsScene::backRect = cocos2d::Rect();
std::string SettingsScene::cn = "";
std::string SettingsScene::jp = "";
std::string SettingsScene::en = "";

Scene* SettingsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingsScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingsScene::init()
{
	if (!Layer::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("assets/" + MainTitleScene::titleBg);
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setAnchorPoint(Point(0.5, 0.5));
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);

	std::vector<std::string>* splVec = Config::getInstance()->getSupportLanguage();
	buttonNum = splVec->size();
	buttonRect = new Rect[buttonNum];
	for (int i = 0; i < buttonNum; ++i)
	{
		//建立button
		auto buttonItem = Label::createWithTTF(getLocalText((*splVec)[i]), "fonts/" + Local::getDefaultFont((*splVec)[i]), 30);
		buttonItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.5 / buttonNum*(i + 1)));
		this->addChild(buttonItem, 2);

		auto buttonBg = Sprite::create("assets/conversationBg.png");
		buttonBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.5 / buttonNum*(i + 1)));
		buttonBg->setScale((buttonItem->getContentSize().width + 50) / buttonBg->getContentSize().width, (buttonItem->getContentSize().height + 20) / buttonBg->getContentSize().height);
		this->addChild(buttonBg, 1);

		buttonRect[i] = buttonBg->getBoundingBox();
	}

	auto labelBack = Label::createWithTTF(Local::back, "fonts/" + Local::getDefaultFont(), 24);
	labelBack->setPosition(Vec2(origin.x + visibleSize.width - labelBack->getContentSize().width / 2 - 30, origin.y + visibleSize.height - labelBack->getContentSize().height / 2 - 30));
	this->addChild(labelBack, 2);
	auto backBg = Sprite::create("assets/conversationBg.png");
	backBg->setPosition(Vec2(origin.x + visibleSize.width - labelBack->getContentSize().width / 2 - 30, origin.y + visibleSize.height - labelBack->getContentSize().height / 2 - 30));
	backBg->setScale((labelBack->getContentSize().width + 50) / backBg->getContentSize().width, (labelBack->getContentSize().height + 20) / backBg->getContentSize().height);
	this->addChild(backBg, 1);
	backRect = backBg->getBoundingBox();

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
			if (backRect.containsPoint(position))
				GameCore::getInstance()->nextStage(-1);
			for (int i = 0; i < buttonNum; ++i)
				if (buttonRect[i].containsPoint(position))
				{
					Config::getInstance()->setLocalLanguage(Config::getInstance()->getSupportLanguage()->at(i));
					GameCore::getInstance()->reload();
					GameCore::getInstance()->nextStage(-1);
				}

		}
	};

	myMouseListener->onMouseUp = [=](Event *event)
	{
		//this->mouse->setScale(0.3f); //鼠标按键抬起，屏幕上的“箭头”尺寸放大
	};

	//将事件监听器与场景绑定
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);


	return true;
}

std::string SettingsScene::getLocalText(std::string local)
{
	if (local == "jp")
		return jp;
	if (local == "cn")
		return cn;
	if (local == "en")
		return en;
	return "unknown";
}