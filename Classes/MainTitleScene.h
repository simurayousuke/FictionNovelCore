#ifndef __MainTitle_Scene_H__
#define __MainTitle_Scene_H__

#include "cocos2d.h"

class MainTitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainTitleScene);
};

#endif // __MainTitle_Scene_H__
