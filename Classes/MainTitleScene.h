#ifndef __MainTitle_Scene_H__
#define __MainTitle_Scene_H__

#include "cocos2d.h"
#include "StatusManager.h"
#include "Local.h"
//本页面按钮字体不能自定义
class MainTitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static std::string titleBg;
	static std::string titleFont;
	static int titleFontSize;
	static std::string bgm;
	static std::string titleContext;
	static std::string start;
	static std::string load;
	static std::string settings;
	static std::string exit;
	static std::string about;
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainTitleScene);
private:
	static cocos2d::Rect* buttonRect;
	static int buttonNum;
};

#endif // __MainTitle_Scene_H__
