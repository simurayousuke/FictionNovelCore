#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"
#include "Local.h"

class LoadScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static void updateLabel(std::string text);
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(LoadScene);
private:
	static cocos2d::Label* labelLoad;
};
#endif // __LOAD_SCENE_H__
