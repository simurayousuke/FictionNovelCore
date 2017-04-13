#include "LoadScene.h"

USING_NS_CC;
cocos2d::Label* LoadScene::labelLoad=NULL;

cocos2d::Scene* LoadScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadScene::init()
{
	if (!Layer::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	labelLoad = Label::createWithTTF(Local::loading, "fonts/" + Local::getDefaultFont(), 24);
	labelLoad->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(labelLoad, 2);

	auto bg = Sprite::create("assets/loading.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setAnchorPoint(Point(0.5, 0.5));
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);
	
	return true;
}

void LoadScene::updateLabel(std::string text)
{
	labelLoad->setString(text);
}