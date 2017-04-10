#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"
#include "StatusManager.h"
#include "Config.h"

class LoadScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(Stage* stg);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	static Stage* stage;
	static int* nextId;
	static int buttonNum;
	static cocos2d::Rect* buttonRect;
	static cocos2d::Rect textRect;
};
#endif // __LOAD_SCENE_H__
