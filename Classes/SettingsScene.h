#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"
#include "GameCore.h"
#include "Config.h"

class SettingsScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SettingsScene);

private:
	static int buttonNum;
	static cocos2d::Rect* buttonRect;
	static cocos2d::Rect backRect;
};
#endif // __SETTINGS_SCENE_H__
